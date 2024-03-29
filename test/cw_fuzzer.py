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

"""
from Fuzzer import Fuzzer
"""
[*] Store/update path to my asm and to original asm in pickle
[*] Ask for a directory with *.s files
[*] Implement all 3 modes of file manipulation
[*] Open all *.s files and store somewhere as originals
[*] Add basic working mode
[*] Add diff comparison of compiling step
[*] Add comparison of generated *.cor files
[*] Add VM fuzzing with *.cor files
"""

if __name__ == '__main__':
    fz = Fuzzer()
    fz.open_asm_files() if fz.args['target'] == 'asm' else fz.open_cor_files()
    print("Check compilation:")
    fz.fuzz()
    if not fz.args['--no-compiled']:
        if fz.cor_files:
            print("Check compiled binaries:")
            fz.check_cor_files()
            print("")
        else:
            print("No binaries were successfully compiled in this session")
    fz.db.wrap_up()
    exit(0 if fz.cnt_errors == 0 else 1)
