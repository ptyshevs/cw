from db import Db
import sys


class Fuzzer:
    def __init__(self):
        self.args = self.parse_args()
        self.db = self.init_db()

    @staticmethod
    def parse_args():
        """Parse CLI arguments"""
        args = {'-u': False}
        for arg in sys.argv[1:]:
            if arg == '-u' or arg == '--update_paths':
                args['-u'] = True
        return args

    @staticmethod
    def usage():
        print("usage: python3 asm_fuzzer.py [-u|--update_paths]")
        print("  -u|--update_paths\t\tShow dialog to update paths to asm binaries")

    def init_db(self):
        db = Db()
        if not db.get('my_asm') or self.args['-u']:
            db.add_record('my_asm', input('Relative path to your asm:'))
        if not db.get('true_asm') or self.args['-u']:
            db.add_record('true_asm', input('Relative path to original asm:'))
        if not db.get('src_dir') or self.args['-u']:
            db.add_record('src_dir', input('Relative path to the directory with *.s files:'))
        return db
