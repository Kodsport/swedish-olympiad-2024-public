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
maxlen = int(cmdlinearg("maxlen", n-1))
alphabet_size = int(cmdlinearg("alphabet_size"))
assert alphabet_size <= 26
letters = [chr(ord('a')+i) for i in range(alphabet_size)]


words = [["a"]] # Always ensure that constructing string of length n is possible
for i in range(m-1):
    w = []
    wlen = random.randint(1, maxlen)
    for j in range(wlen):
        w.append(random.choice(letters))
    words.append(w)

t = []
while len(t)<n:
    w = random.choice(words)
    if len(t)+len(w)<=n:
        t.extend(w)
print(n)
print("".join(t))
print(m)
for w in words:
    print("".join(w))