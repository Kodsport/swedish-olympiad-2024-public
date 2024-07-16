#!/usr/bin/python3

import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
m = int(cmdlinearg('m'))
maxlen = int(cmdlinearg("maxlen"))
perturb = int(cmdlinearg("perturb",10))

import itertools
import string

# Get the alphabet
alphabet = string.ascii_lowercase

# Generate all 4-letter strings using itertools.product
all_strings = [''.join(chars) for chars in itertools.product(alphabet, repeat=4)]
del all_strings[0]

words = [["a"]] # Always ensure that constructing string of length n is possible
i = 0
totlen = 1
while len(words)<m:
    
    words.append("a"*(maxlen-random.randint(0,perturb))+all_strings[i])
    totlen += len(words[-1])
    if totlen > int(1e6):
        del words[-1]
        break
    i+=1


print(n)
print("a"*n)
print(len(words))
for w in words:
    print("".join(w))