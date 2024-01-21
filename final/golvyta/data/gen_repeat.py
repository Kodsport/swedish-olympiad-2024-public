#!/usr/bin/python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

MAXN = 3*10**5

D = {'>': (0,1), '<': (0,-1), 'v': (1,0), '^': (-1,0)}
dirs = ['>', '<', 'v', '^']

length = int(cmdlinearg("n"))
char = cmdlinearg("char", ">")

r = int(cmdlinearg("r", 0))
c = int(cmdlinearg("c", 0))

print(length)
s = "".join(char*length)
print(s)
print(r,c)


