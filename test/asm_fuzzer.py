#!/usr/local/bin/python3
import sys
import pickle

"""
Start by selecting *k* random places and len *l* for each of those places.
There are three different things that we can do:
1) remove substring, starting from k till k+l
2) insert l random characters in k-th position
3) replace l characters with random characters, starting from k
"""

"""
[*] Store/update path to my asm and to original asm in pickle
[ ] Ask for a directory with *.cor files
[ ] Implement all 3 modes of file manipulation
"""


class Db:
    def __init__(self, dbname='db.pcl'):
        self.dbname = dbname
        self.pcl = dict()
        try:
            with open(self.dbname, 'rb') as f:
                self.pcl = pickle.load(f)
        except FileNotFoundError:
            pass

    def add_record(self, k, v):
        """Add or update record"""
        self.pcl[k] = v

    def get(self, k):
        return self.pcl[k] if k in self.pcl.keys() else None

    def wrap_up(self):
        with open(self.dbname, 'wb') as f:
            pickle.dump(self.pcl, f)


def parse_args():
    """Parse CLI arguments"""
    args = dict()
    for arg in sys.argv[1:]:
        if arg == '-u' or arg == '--update_paths':
            args['-u'] = True
    return args


def usage():
    print("usage: python3 asm_fuzzer.py [-u|--update_paths]")
    print("  -u|--update_paths\t\tShow dialog to update paths to asm binaries")


def init_db():
    db = Db()
    if not db.get('my_asm'):
        db.add_record('my_asm', input('Relative path to your asm:'))
    if not db.get('true_asm'):
        db.add_record('true_asm', input('Relative path to original asm:'))
    return db


class Fuzzer:
    def __init__(self):
        self.args = parse_args()
        self.db = init_db()


if __name__ == '__main__':
    # fz = Fuzzer()
    # fz.db.wrap_up()
