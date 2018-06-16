#!/usr/local/bin/python3
"""
Start by selecting *k* random places and len *l* for each of those places.
There are three different things that we can do:
1) remove substring, starting from k till k+l
2) insert l random characters in k-th position
3) replace l characters with random characters, starting from k

Algorithm goes like this:
  - from the list of valid *.s files, select one:
    - open it and read its content
    - modify it, applying 3 operations defined above to m random places in file
    - store new file in the temporary location
    - run original asm on it and record its output
    - run my_asm and compare its input with the original one
      if the output is identical, remove the file
  - select new file, repeat until satisfied

Thus, the severety of file modification depends on:
- number of m trials to select new random place k
- length of modified chunk l
Hence, it is easy to define different levels of "hardness", which would regulate k and l so to make changes larger or
smaller.

WARNING: only the output is compared, not the files generated (comes in the future releases)
"""
from fuzzer import Fuzzer
import sys
import random
import string
"""
[*] Store/update path to my asm and to original asm in pickle
[*] Ask for a directory with *.s files
[*] Implement all 3 modes of file manipulation
[ ] Record good *.s files to the database
"""
mild_charset = '!"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\]^_`abcdefghijklmnopqrstuvwxyz{|}~'
specs = ";\"'#$%^&*()[],-.=>?\|/\\}{"
spaces = [9, 10, 11, 12, 13, 32]
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
        if random.randint(0, 9) == 0: # convert to uppercase
            i = random.randrange(0, length - 1)
            s = s[:i] + s[i].upper() + s[i+1:]
        if random.randint(0, 4) < 4:
            return s + ':'
        else:
            i = random.randrange(0, length)
            return s[:i] + ':' + s[i:]
    elif mode == 'bizarre':
        return ''.join([chr(random.randint(0, 30000)) for _ in range(length)])
    elif mode == 'spec':
        i = random.randint(0, 1)  # beginning or end
        spec = random.choice(specs)
        s = ''.join([random.choice(string.ascii_lowercase) for _ in range(length - 1)])
        return spec + s if i else s + spec
    elif mode == 'spaces':
        return ''.join([chr(random.choice(spaces)) for _ in range(length)])
    else:
        raise ValueError("mode is not recognized:", mode)

def remove(file, n, k, l):
    """Remove k+l segment"""
    file[n] = file[n][:k] + file[n][k + l:]


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
    file[n] = file[n][:k + 1] + gen_rand_string(mode, l) + file[n][k+1:]

def replace(file, n, k, l, mode='spec'):
    """
    Replace l characters, starting from k with random values
    :param file: file's content
    :param n: random line selected
    :param k: random position on the line
    :param l: length of changed segment
    :param mode: Mode of operation
    """
    file[n] = file[n][:k] + gen_rand_string(mode, l) + file[n][k+l:]

def open_file(filename):
    with open(filename, 'r') as f:
        return f.readlines()


def select_random_location(file: list):
    """Find a new random position (n, k) in a file, where n - line, and k - position in a line"""
    n = random.randrange(0, len(file))
    k = random.randrange(0, len(file[n]))
    return n, k


if __name__ == '__main__':
    file = open_file(sys.argv[1])
    operations = [("insert", insert), ("remove", remove), ("replace", replace)]
    l = 3
    for i in range(10):
        opname, op = random.choice(operations)
        print("op selected:", opname)
        n, k = select_random_location(file)
        print("orig:", file[n])
        op(file, n, k, l)
        print("mod:", file[n])
    # fz = Fuzzer()
    # fz.db.wrap_up()
