import subprocess
import random
import string


specs = ";\"'#$%^&*()[],-.=>?\|/\\}{"
spaces = [9, 10, 11, 12, 13, 32]

def run_command(command: str):
    """Run command, capture output (STDOUT and STDERR combined) and return value"""
    complete = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    return complete.returncode, str(complete.stdout, 'utf-8')


def rename_file(filename, new_filename):
    """Give a new name to the <filename>"""
    cpy_command = "mv {} {}".format(filename, new_filename)
    subprocess.run(cpy_command, shell=True, stderr=subprocess.STDOUT)

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
        if len(s) and random.randint(0, 9) == 0:  # convert to uppercase
            i = random.randrange(0, length - 1) if length - 1 > 0 else 0
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
        spec = random.choice(specs) if random.randint(0, 1) else random.choice(string.ascii_letters)
        s = ''.join([random.choice(string.ascii_lowercase) for _ in range(length - 1)])
        return spec + s if i else s + spec
    elif mode == 'spaces':
        return ''.join([chr(random.choice(spaces)) for _ in range(length)])
    else:
        raise ValueError("mode is not recognized:", mode)

def remove(file, n, k, l, mode, type='str'):
    """Remove k+l segment"""
    file[n] = file[n][:k] + file[n][k + l:]

def insert(file, n, k, l, mode='spec', type='str'):
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
    stub = gen_rand_string(mode, l)
    file[n] = file[n][:k + 1] + stub if type == 'str' else bytes(stub,  encoding='utf-8') + file[n][k + 1:]

def replace(file, n, k, l, mode='spec', type='str'):
    """
    Replace l characters, starting from k with random values
    :param file: file's content
    :param n: random line selected
    :param k: random position on the line
    :param l: length of changed segment
    :param mode: Mode of operation
    :param type: is it an *.s (string) file or *.cor (binary) one?
    """
    stub = gen_rand_string(mode, l)
    file[n] = file[n][:k] + stub if type == 'str' else bytes(stub, encoding='utf-8') + file[n][k + l:]

def open_file(filename: str) -> list:
    """Open file and return its content"""
    with open(filename, 'r') as f:
        return f.readlines()

def select_random_location(file: list):
    """Find a new random position (n, k) in a file, where n - line, and k - position in a line"""
    n = random.randrange(0, len(file)) if len(file) > 0 else 0
    k = random.randrange(0, len(file[n])) if len(file[n]) > 0 else 0
    return n, k


modes = ['digits', 'label', 'bizarre', 'spec', 'spaces']
operations = [("insert", insert), ("remove", remove), ("replace", replace)]
