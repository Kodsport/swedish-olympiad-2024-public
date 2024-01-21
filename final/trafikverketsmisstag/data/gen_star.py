#!/usr/bin/python3

import sys
import random
import math
from random import randint

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
k = int(cmdlinearg('k'))
mode = cmdlinearg('mode')

print(n,k)
for i in range(1,n):
    print(1,i+1)

if mode == "random":
    starts = random.sample(range(1,n), k)
    for i in range(k):
        start = starts[i]
        stop = random.choice(range(1,n))
        if stop == start:
            stop = 0
        print(start+1,stop+1)
elif mode == "cycle":
    for i in range(k):
        if i == k-1:
            print(i+2,2)
        else:
            print(i+2,i+3)
elif mode == "path":
    for i in range(k):
        if i == k-1:
            print(i+2,1)
        else:
            print(i+2,i+3)
