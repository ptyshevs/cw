from Db import Db
import os
import shutil
import sys
import subprocess
import random
import string

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
    specs = ";\"'#$%^&*()[],-.=>?\|/\\}{"
    spaces = [9, 10, 11, 12, 13, 32]

    def __init__(self):
        self.args = self.parse_args()
        self.db = self.init_db()
        self.operations = [("insert", Fuzzer.insert), ("remove", Fuzzer.remove), ("replace", Fuzzer.replace)]
        self.modes = {'easy': (1, 1), 'moderate': (5, 5), 'hard': (8, 8)}
        self.cnt_errors = 0
        self.files = dict()
        self.cor_files = list()
        self.out_dir = 'traces'
        self.file_compiled_prefix = "Writing output program to "
        self.m, self.l = self.modes[self.args['fuzz_mode']]
        if not os.path.exists(self.out_dir):
            os.makedirs(self.out_dir)

    def open_files(self):
        """Find all files with *.s extension in src_dir"""
        for file in os.listdir(self.db.get('src_dir' if self.args['target'] == 'asm' else 'cw_dir')):
            if self.args['target'] == 'asm' and file.endswith(".s") and file not in self.files.keys():
                path = os.path.join(self.db.get('src_dir'), file)
                with open(path) as f:
                    self.files[path] = f.readlines()
            elif self.args['target'] == 'corewar' and file.endswith(".cor"):
                path = os.path.join(self.db.get('cw_dir'), file)
                with open(path, 'rb') as f:
                    self.files[path] = f.readlines()

    def asm_run(self, mod_filename):
        """Compare original asm output with your version"""
        orig_command = "{} {}".format(self.db.get('true_asm'), mod_filename)
        my_command = "{} {}".format(self.db.get('my_asm'), mod_filename)

        mod_base = mod_filename[:-2]
        orig_cor_fname = None

        try:  # Normal execution
            orig_output = subprocess.check_output(orig_command, shell=True, stderr=subprocess.STDOUT).decode('ascii')
        except subprocess.CalledProcessError as e:  # Error
            orig_output = str(e.output, encoding='utf-8')
        if orig_output.startswith(self.file_compiled_prefix):
            # Copy the original *.cor file, so it is not over-written for later comparison
            orig_cor_fname = mod_base + ".cor"
            cpy_command = "cp {0} {1}; rm {0}".format(orig_cor_fname, mod_base + ".orig_cor")
            subprocess.check_output(cpy_command, shell=True, stderr=subprocess.STDOUT)
        try:  # Same here
            mod_output = subprocess.check_output(my_command, shell=True, stderr=subprocess.STDOUT).decode('ascii')
        except subprocess.CalledProcessError as e:
            mod_output = str(e.output, encoding='utf-8')
        if mod_output.startswith(self.file_compiled_prefix) and orig_cor_fname:
            self.cor_files.append((mod_base + ".cor", mod_base + ".orig_cor"))
        return orig_output, mod_output

    def cor_run(self, filename):
        """Run corewar binaries"""
        orig_command = "{} {}".format(self.db.get('true_cw'), filename)
        my_command = "{} {}".format(self.db.get('my_cw'), filename)

        try:
            orig_output = subprocess.check_output(orig_command, shell=True, stderr=subprocess.STDOUT).decode('utf-8')
        except subprocess.CalledProcessError as e:
            orig_output = str(e.output, encoding='utf-8')
        try:  # Same here
            mod_output = subprocess.check_output(my_command, shell=True, stderr=subprocess.STDOUT).decode('ascii')
        except subprocess.CalledProcessError as e:
            mod_output = str(e.output, encoding='utf-8')
        return orig_output, mod_output

    def cor_fuzz_once(self):
        filename, file = random.choice(list(self.files.items()))
        file = self.mod_file(file, self.m, 'digits')
        mod_dir, mod_filename = self.save_file(file, filename)
        orig_out, mod_out = self.cor_run(mod_filename)
        if orig_out != mod_out:
            self.cnt_errors += 1
            Fuzzer.diff_files(filename, mod_filename)
            Fuzzer.save_output(orig_out, mod_out, mod_filename)
            if self.args['v']:
                print("Output differs for file {}".format(mod_filename))
            else:
                print("{}.{}".format(RED, NC), end='')
        else:
            if not (orig_out.startswith(self.file_compiled_prefix) and mod_out.startswith(self.file_compiled_prefix)):
                shutil.rmtree(mod_dir)  # remove the whole directory, but only if the *.cor files weren't not generated
            if self.args['v']:
                print("Output matches the original version")
            else:
                print("{}.{}".format(GREEN, NC), end='')

    def fuzz_once(self):
        filename, file = random.choice(list(self.files.items()))
        file = self.mod_file(file, self.m)
        mod_dir, mod_filename = self.save_file(file, filename)
        orig_out, mod_out = self.asm_run(mod_filename)
        if orig_out != mod_out:
            self.cnt_errors += 1
            Fuzzer.diff_files(filename, mod_filename)
            Fuzzer.save_output(orig_out, mod_out, mod_filename)
            if self.args['v']:
                print("Output differs for file {}".format(mod_filename))
            else:
                print("{}.{}".format(RED, NC), end='')
        else:
            if not (orig_out.startswith(self.file_compiled_prefix) and mod_out.startswith(self.file_compiled_prefix)):
                shutil.rmtree(mod_dir)  # remove the whole directory, but only if the *.cor files weren't not generated
            if self.args['v']:
                print("Output matches the original version")
            else:
                print("{}.{}".format(GREEN, NC), end='')

    def fuzz(self):
        """Fuzz the compilation step, storing all successfully compiled *.cor files"""
        self.cnt_errors = 0
        for i in range(self.args['n']):
            self.fuzz_once()
        if not self.args['v']:
            print("")
        if self.cnt_errors != 0:
            print("You can find all cases there haven't matched in traces directory")

    @staticmethod
    def check_cor_files(cor_files: list):
        """Compare all *.cor file pairs of format (*.orig_cor, *.mod_cor)"""
        for orig, mod in cor_files:
            orig_xxd, mod_xxd = orig[:-8] + '.orig_xxd', mod[:-3] + '.xxd'
            diff_xxd = mod[:-3] + '.xxd_diff'
            cmd = "xxd -g 2 {0} > {1}; xxd -g 2 {2} > {3}; diff {1} {3} > {4}; rm {1} {3}".format(
                orig, orig_xxd, mod, mod_xxd, diff_xxd)
            try:
                out = subprocess.check_output(cmd, stderr=subprocess.STDOUT, shell=True).decode('utf-8')
            except subprocess.CalledProcessError as e:
                out = str(e.output, encoding='utf-8')
            print(out)

    def mod_file(self, file, m, mode='spec'):
        """Modify file content by copying it."""
        mod_file = [line for line in file]
        for i in range(m):
            opname, op = random.choice(self.operations)
            n, k = self.select_random_location(mod_file)
            op(mod_file, n, k, self.l, mode)
        return mod_file

    @staticmethod
    def gen_rand_string(mode, length):
        """
        Generate random string. Available modes:
        1) "digits" - Digits only, with optional sign at the beginning
        2) "label" - Label-like (lowercase and with `:` in random places)
        3) "bizarre" - Non-sense (complete Unicode charset)
        4) "spec" - Start or end with a special character
        5) "spaces" - string containing spaces only
        :param mode: mode of operation
        :param length: length of the desired string
        :return: The random string
        """
        if mode == 'digits':
            s = ''
            if random.randint(0, 2) == 0:  # one third of all digit strings would contain a sign
                s = '+' if random.randint(0, 1) == 1 else '-'
            return s + ''.join([random.choice(string.digits) for _ in range(length if len(s) == 0 else length - 1)])
        elif mode == 'label':
            s = ''.join([random.choice(string.ascii_lowercase) for _ in range(length - 1)])
            if random.randint(0, 9) == 0:  # convert to uppercase
                i = random.randrange(0, length - 1)
                s = s[:i] + s[i].upper() + s[i + 1:]
            if random.randint(0, 4) < 4:
                return s + ':'
            else:
                i = random.randrange(0, length)
                return s[:i] + ':' + s[i:]
        elif mode == 'bizarre':
            return ''.join([chr(random.randint(0, 30000)) for _ in range(length)])
        elif mode == 'spec':
            i = random.randint(0, 1)  # beginning or end
            spec = random.choice(Fuzzer.specs) if random.randint(0, 1) else random.choice(string.ascii_letters)
            s = ''.join([random.choice(string.ascii_lowercase) for _ in range(length - 1)])
            return spec + s if i else s + spec
        elif mode == 'spaces':
            return ''.join([chr(random.choice(Fuzzer.spaces)) for _ in range(length)])
        else:
            raise ValueError("mode is not recognized:", mode)

    @staticmethod
    def remove(file, n, k, l, mode):
        """Remove k+l segment"""
        file[n] = file[n][:k] + file[n][k + l:]

    @staticmethod
    def insert(file, n, k, l, mode='spec'):
        """
            insert l random characters in k-th position

            There are two :
            1) Add complete nonsense from almost whole UTF-8 charset
            2) Add english chars
        :param file: file's content
        :param n: random line selected
        :param k: random position on the line
        :param l: length of changed segment
        :param mode: Mode of operation
        :return: Nothing
        """
        file[n] = file[n][:k + 1] + Fuzzer.gen_rand_string(mode, l) + file[n][k + 1:]

    @staticmethod
    def replace(file, n, k, l, mode='spec'):
        """
        Replace l characters, starting from k with random values
        :param file: file's content
        :param n: random line selected
        :param k: random position on the line
        :param l: length of changed segment
        :param mode: Mode of operation
        """
        file[n] = file[n][:k] + Fuzzer.gen_rand_string(mode, l) + file[n][k + l:]

    @staticmethod
    def open_file(filename: str) -> list:
        """Open file and return its content"""
        with open(filename, 'r') as f:
            return f.readlines()

    @staticmethod
    def select_random_location(file: list):
        """Find a new random position (n, k) in a file, where n - line, and k - position in a line"""
        n = random.randrange(0, len(file))
        k = random.randrange(0, len(file[n])) if len(file[n]) > 0 else 0
        return n, k

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
        new_filename = os.path.join(self.out_dir, test_dir, os.path.basename(filename)[:-2] + '.s')
        with open(new_filename, 'w+') as f:
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

    @staticmethod
    def save_output(orig_out, mod_out, mod_filename):
        """Save shell output. STDOUT is combined with STDERR"""
        with open(mod_filename[:-2] + '.out', 'w+') as f:
            f.write("Original output:\n*********************************\n{}*********************************\n".format(orig_out))
            f.write("Your output:\n*********************************\n{}*********************************\n".format(mod_out))

    @staticmethod
    def parse_args():
        """Parse CLI arguments"""
        args = {'-u': False, 'n': 40, 'fuzz_mode': 'easy', 'v': False, 'target': 'asm'}
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
            elif arg == '-h':
                Fuzzer.usage()
                exit(0)
        return args

    @staticmethod
    def usage():
        """Display usage"""
        print("usage: python3 asm_fuzzer.py [-u|--update_paths] [-n <n_tests>] [--hard] [-v|--verbose] [-m|--mode <asm|corewar>]")
        print("\nasm_fuzzer - test your asm compiler by randomly introducing changes to original files.\n")
        print("  -u|--update_paths\tShow dialog to update paths to asm/corewar binaries")
        print("  -n\t\t\tAmount of tests to run")
        print("  -v|--verbose\t\tVerbose mode")
        print("  --hard\t\tFiles are modified more")
        print("  mode\t\tSelect the fuzzing target. asm by default")

    def init_db(self):
        """Initialize database"""
        db = Db()
        if self.args['target'] == 'asm':
            if not db.get('my_asm') or self.args['-u']:
                db.add_record('my_asm', input('Relative path to your asm:'))
            if not db.get('true_asm') or self.args['-u']:
                db.add_record('true_asm', input('Relative path to original asm:'))
            if not db.get('src_dir') or self.args['-u']:
                db.add_record('src_dir', input('Relative path to the directory with *.s files:'))
        elif self.args['target'] == 'corewar':
            if not db.get('my_cw') or self.args['-u']:
                db.add_record('my_cw', input("Relative path to your corewar:"))
            if not db.get('true_cw') or self.args['-u']:
                db.add_record('true_cw', input("Relative path to original corewar:"))
            if not db.get('cw_dir') or self.args['-u']:
                db.add_record('cw_dir', input('Relative path to the directory with *.cor files:'))
        return db
