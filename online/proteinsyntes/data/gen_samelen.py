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

import itertools
import string

# Get the alphabet
alphabet = string.ascii_lowercase

# Generate all 4-letter strings using itertools.product
words = [''.join(chars) for chars in itertools.product(alphabet, repeat=4)]

while len(words)*4>int(1e6):
    del words[-1]


t = []
while len(t)<n:
    w = random.choice(words)
    if len(t)+len(w)<=n:
        t.extend(w)
print(len(t))
print("".join(t))
print(len(words))
random.shuffle(words)
for w in words:
    print("".join(w))

