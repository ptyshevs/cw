from Db import Db
import os
import shutil
import sys
import subprocess
import random
import string
import helpers

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m'

class Fuzzer:

    def __init__(self):
        self.args = self.parse_args()
        self.db = self.init_db()
        self.modes = {'easy': (1, 1), 'moderate': (5, 5), 'hard': (8, 8)}
        self.cnt_errors = 0
        self.files = dict()
        self.cor_files = list()
        self.ext = ".s" if self.args['target'] == 'asm' else ".cor"
        self.out_dir = 'traces'
        self.file_compiled_prefix = "Writing output program to "
        self.m, self.l = self.modes[self.args['fuzz_mode']]
        if not os.path.exists(self.out_dir):
            os.makedirs(self.out_dir)

    def open_cor_files(self):
        for file in os.listdir(self.db.get('src_dir')):
            if file.endswith(".s"):
                path = os.path.join(self.db.get('src_dir'), file)
                compile_cmd = "{} {}".format(self.db.get('true_asm'), path)
                try:
                    subprocess.check_output(compile_cmd, shell=True, stderr=subprocess.STDOUT)
                    with open(path[:-2] + self.ext, 'rb') as f:
                        self.files[path] = f.readlines()
                except subprocess.CalledProcessError:
                    pass
        if len(self.files) == 0:
            print("No {} files found".format("*" + self.ext))
            exit(1)

    def open_asm_files(self):
        """Find all files with *.s extension in src_dir"""
        for file in os.listdir(self.db.get('src_dir')):
            if file.endswith(".s") and file not in self.files.keys():
                path = os.path.join(self.db.get('src_dir'), file)
                with open(path) as f:
                    self.files[path] = f.readlines()
        if len(self.files) == 0:
            print("No {} files found".format("*" + self.ext))
            exit(1)

    def asm_run(self, mod_filename):
        """Compare original asm output with your version"""
        file_base = mod_filename[:-2]
        orig_cor = file_base + ".orig_cor"
        cor = file_base + ".cor"

        orig_ret, orig_out = helpers.run_command("{} {}".format(self.db.get('true_asm'), mod_filename))
        if orig_out.startswith(self.file_compiled_prefix):
            # Copy the original *.cor file, so it is not over-written for later comparison
            helpers.rename_file(cor, orig_cor)
        mod_ret, mod_out = helpers.run_command("{} {}".format(self.db.get('my_asm'), mod_filename))
        if os.path.exists(cor) and os.path.exists(orig_cor):  # save *.cor and *.orig_cor files for binaries diff
            self.cor_files.append((cor, orig_cor))
        return {'ret': orig_ret, 'out': orig_out, 'file': orig_cor}, {'ret': mod_ret, 'out': mod_out, 'file': cor}

    def cor_run(self, filename):
        """Run corewar binaries"""
        orig_command = "{} {}".format(self.db.get('true_cw'), filename)
        my_command = "{} {}".format(self.db.get('my_cw'), filename)

        orig_ret, orig_out = helpers.run_command(orig_command)
        mod_ret, mod_out = helpers.run_command(my_command)
        return {'ret': orig_ret, 'out': orig_out}, {'ret': mod_ret, 'out': mod_out}

    def log(self, message, good_outcome: bool):
        if not self.args['v']:
            print("{}.{}".format(GREEN if good_outcome else RED, NC), end='')
        else:
            print(message)

    def cor_fuzz_once(self):
        filename, file = random.choice(list(self.files.items()))
        file = self.mod_file(file, self.m, 'digits', tpe='bytes')
        mod_dir, mod_filename = self.save_file(file, filename)
        orig, mod = self.cor_run(mod_filename)
        if (orig['ret'] == 0 or orig['ret'] == -1) and orig['out'] != mod['out']:
            self.cnt_errors += 1
            self.save_output(orig['out'], mod['out'], mod_filename)
            self.log("Output differs for file {}".format(mod_filename), False)
        else:
            if not (orig['out'].startswith(self.file_compiled_prefix) and mod['out'].startswith(self.file_compiled_prefix)):
                shutil.rmtree(mod_dir)  # remove the whole directory, but only if the *.cor files weren't not generated
            self.log("Output matches the original version", True)

    def asm_fuzz_once(self):
        filename, file = random.choice(list(self.files.items()))
        file = self.mod_file(file, self.m, tpe='str')
        mod_dir, mod_filename = self.save_file(file, filename)
        orig, mod = self.asm_run(mod_filename)
        if (orig['ret'] == 0 or orig['ret'] == -1) and orig['out'] != mod['out']:
            self.cnt_errors += 1
            Fuzzer.diff_files(filename, mod_filename)
            self.save_output(orig['out'], mod['out'], mod_filename)
            self.log("Output differs for file {}".format(mod_filename), False)
        else:
            if not (os.path.exists(orig['file']) and os.path.exists(mod['file'])):
                shutil.rmtree(mod_dir)  # remove the whole directory, but only if the *.cor files weren't not generated
            self.log("Output matches the original version", True)

    def fuzz(self):
        """Fuzz the compilation step, storing all successfully compiled *.cor files"""
        self.cnt_errors = 0
        for i in range(self.args['n']):
            self.asm_fuzz_once() if self.args['target'] == 'asm' else self.cor_fuzz_once()
            if i > 0 and i % 80 == 0 and not self.args['v']:
                print("")
        if not self.args['v']:
            print("")
        if self.cnt_errors != 0:
            print("You can find all cases there haven't matched in traces directory")

    def check_cor_files(self):
        """Compare all *.cor file pairs of format (*.orig_cor, *.mod_cor)"""
        i = 0
        for mod, orig in self.cor_files:
            orig_xxd, mod_xxd = orig[:-3] + 'xxd', mod[:-3] + 'xxd'
            diff_xxd = mod[:-3] + 'xxd_diff'
            cmd = "xxd -g 2 {0} > {1}; xxd -g 2 {2} > {3}; diff {1} {3} > {4}; rm -rf {1} {3}".format(
                orig, orig_xxd, mod, mod_xxd, diff_xxd)
            ret, out = helpers.run_command(cmd)
            if ret != 0:
                self.log("Compiled version differs for {}".format(mod), False)
            else:
                self.log("Compiled binaries match", True)
                path, file = os.path.split(mod)
                shutil.rmtree(path)
            if i > 0 and i % 80 == 0 and not self.args['v']:
                print('')
            i += 1

    def mod_file(self, file, m, mode=None, tpe='str'):
        """Modify file content by copying it."""
        mod_file = [line for line in file]
        for i in range(m):
            if mode is None:
                mode = random.choice(helpers.modes)
            opname, op = random.choice(helpers.operations)
            n, k = helpers.select_random_location(mod_file)
            op(mod_file, n, k, self.l, mode, tpe)
        return mod_file

    def save_file(self, file, filename):
        """
        Generate filename
        :param file: file content
        :param filename: of the file
        :return: None
        """
        test_dir = ''.join([random.choice(string.ascii_lowercase) for _ in range(20)])
        dir_path = os.path.join(self.out_dir, test_dir)
        os.makedirs(dir_path)
        basename = os.path.basename(filename)[:-2]
        new_filename = os.path.join(self.out_dir, test_dir, basename + self.ext)
        with open(new_filename, 'w+' if self.args['target'] == 'asm' else 'wb+', encoding='utf-8') as f:
            f.writelines(file)
        return dir_path, new_filename

    @staticmethod
    def diff_files(orig_filename, mod_filename):
        """Save diff of modified file and the original in the traces"""
        diff_filename = mod_filename[:-2] + ".diff"
        try:
            subprocess.check_output("diff {} {} > {}".format(orig_filename, mod_filename, diff_filename),
                                    shell=True, stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as e:  # if diff found discrepancy, it returns 1. Nothing special here
            pass

    def save_output(self, orig_out, mod_out, mod_filename):
        """Save shell output. STDOUT is combined with STDERR"""
        with open(mod_filename[:-2 if self.args['target'] == 'asm' else -4] + '.out', 'w+') as f:
            f.write("Original output:\n*********************************\n{}*********************************\n".format(orig_out))
            f.write("Your output:\n*********************************\n{}*********************************\n".format(mod_out))

    def parse_args(self):
        """Parse CLI arguments"""
        args = {'-u': False, 'n': 40, 'fuzz_mode': 'easy', 'v': False, 'target': 'asm', '--no-compiled': False,
                'db': 'db.pcl'}
        for i, arg in enumerate(sys.argv[1:]):
            if arg == '-u' or arg == '--update_paths':
                args['-u'] = True
            elif arg == '-n' and sys.argv[i + 2].isdecimal():
                args['n'] = int(sys.argv[i + 2])
            elif arg == '--hard':
                args['mode'] = 'hard'
            elif arg == '-v' or arg == '--verbose':
                args['v'] = True
            elif arg == '-m' or arg == '--mode':
                if sys.argv[i + 2] == 'asm' or sys.argv[i + 2] == 'corewar':
                    args['target'] = sys.argv[i + 2]
                else:
                    raise ValueError("Unrecognized mode:", sys.argv[i + 2])
            elif arg == '--no-compiled':
                args['--no-compiled'] = False
            elif arg == '-db':
                args['db'] = sys.argv[i + 2]
            elif arg == '-h':
                Fuzzer.usage()
                exit(0)
        return args

    @staticmethod
    def usage():
        """Display usage"""
        print("usage: python3 cw_fuzzer.py [-u|--update_paths] [-n <n_tests>] [--hard] [-v|--verbose]"
              "[-m|--mode <asm|corewar>] [--no-compiled] [-db <db_path>]")
        print("\nasm_fuzzer - test your asm compiler by randomly introducing changes to original files.\n")
        print("  -n\t\t\tAmount of tests to run")
        print("  -m --mode\t\t\tSelect the fuzzing target. asm by default")
        print("  --hard\t\tFiles are modified more")
        print("  -u --update_paths\tShow dialog to update paths to asm/corewar binaries")
        print("  --no-compiled\t\tDon't check the *.cor files generated by asm fuzzer")
        print("  -db\t\tProvide path to *.pcl file with variables")
        print("  -v --verbose\t\tVerbose mode")

    def init_db(self):
        """Initialize database"""
        db = Db(self.args['db'])
        if self.args['target'] == 'asm':
            if not db.get('my_asm') or self.args['-u']:
                db.add_record('my_asm', input('Relative path to your asm:'))
            if not db.get('true_asm') or self.args['-u']:
                db.add_record('true_asm', input('Relative path to original asm:'))
        elif self.args['target'] == 'corewar':
            if not db.get('my_cw') or self.args['-u']:
                db.add_record('my_cw', input("Relative path to your corewar:"))
            if not db.get('true_cw') or self.args['-u']:
                db.add_record('true_cw', input("Relative path to original corewar:"))
            if not db.get('true_asm') or self.args['-u']:
                db.add_record('true_asm', input('Relative path to original asm:'))

        if not db.get('src_dir') or self.args['-u']:
            db.add_record('src_dir', input('Relative path to the directory with *.s files:'))
        return db
