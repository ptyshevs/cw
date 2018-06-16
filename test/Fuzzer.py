from Db import Db
import os
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
        self.files = dict()
        self.out_dir = 'traces'
        self.m, self.l = self.modes[self.args['mode']]
        if not os.path.exists(self.out_dir):
            os.makedirs(self.out_dir)

    def open_files(self):
        """Find all files with *.s extension in src_dir"""
        for file in os.listdir(self.db.get('src_dir')):
            if file.endswith(".s") and file not in self.files.keys():
                with open(self.db.get('src_dir') + "/" + file) as f:
                    self.files[file] = f.readlines()

    def asm_run(self, mod_filename):
        """Compare original asm output with your version"""
        orig_command = "{} {}".format(self.db.get('true_asm'), mod_filename)
        my_command = "{} {}".format(self.db.get('my_asm'), mod_filename)
        try:  # Normal execution
            orig_output = subprocess.check_output(orig_command, shell=True, stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as e:  # Error
            orig_output = str(e.output, encoding='utf-8')
        try:  # Same here
            mod_output = subprocess.check_output(my_command, shell=True, stderr=subprocess.STDOUT)
        except subprocess.CalledProcessError as e:
            mod_output = str(e.output, encoding='utf-8')
        return orig_output, mod_output

    def fuzz_once(self):
        filename, file = random.choice(list(self.files.items()))
        file = self.mod_file(file, self.m)
        mod_filename = self.save_file(file, filename)
        orig_out, mod_out = self.asm_run(mod_filename)
        if orig_out != mod_out:
            if self.args['v']:
                print("Output differs for file {}".format(mod_filename))
            else:
                print("{}.{}".format(RED, NC), end='')
        else:
            os.remove(mod_filename)
            if self.args['v']:
                print("Output matches the original version")
            else:
                print("{}.{}".format(GREEN, NC), end='')

    def fuzz(self):
        for i in range(self.args['n']):
            self.fuzz_once()
        if not self.args['v']:
            print("")

    def mod_file(self, file, m):
        """Modify file content by copying it."""
        mod_file = [line for line in file]
        for i in range(m):
            opname, op = random.choice(self.operations)
            n, k = self.select_random_location(mod_file)
            op(mod_file, n, k, self.l)
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
    def remove(file, n, k, l):
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
    def open_file(filename):
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
        :param filename of the file
        :return: None
        """
        new_filename = os.path.join(self.out_dir, os.path.basename(filename)[:-2] + ''.join(
            [random.choice(string.ascii_lowercase) for _ in range(20)]) + '.s')
        with open(new_filename, 'w+') as f:
            f.writelines(file)
        return new_filename

    @staticmethod
    def parse_args():
        """Parse CLI arguments"""
        args = {'-u': False, 'n': 40, 'mode': 'easy', 'v': False}
        for i, arg in enumerate(sys.argv[1:]):
            if arg == '-u' or arg == '--update_paths':
                args['-u'] = True
            elif arg == '-n' and sys.argv[i + 2].isdecimal():
                args['n'] = int(sys.argv[i + 2])
            elif arg == '--hard':
                args['mode'] = 'hard'
            elif arg == '-v' or arg == '--verbose':
                args['v'] = True
            elif arg == '-h':
                Fuzzer.usage()
                exit(0)
        return args

    @staticmethod
    def usage():
        print("usage: python3 asm_fuzzer.py [-u|--update_paths] [-n <n_tests>] [--hard] [-v|--verbose]")
        print("\nasm_fuzzer - test your asm compiler by randomly introducing changes to original files.\n")
        print("  -u|--update_paths\tShow dialog to update paths to asm binaries")
        print("  -n\t\t\tAmount of tests to run")
        print("  -v|--verbose\t\tVerbose mode")
        print("  --hard\t\tFiles are modified more")

    def init_db(self):
        db = Db()
        if not db.get('my_asm') or self.args['-u']:
            db.add_record('my_asm', input('Relative path to your asm:'))
        if not db.get('true_asm') or self.args['-u']:
            db.add_record('true_asm', input('Relative path to original asm:'))
        if not db.get('src_dir') or self.args['-u']:
            db.add_record('src_dir', input('Relative path to the directory with *.s files:'))
        return db
