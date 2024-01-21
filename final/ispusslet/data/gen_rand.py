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
m = int(cmdlinearg("m", n))
x = int(cmdlinearg('x'))
ret = int(cmdlinearg('r'))
#randint(1,int(cmdlinearg("maxx")))
grid = [['.' for i in range(m)] for j in range(n)]
positions = [(i,j) for i in range(n) for j in range(m)]

random.shuffle(positions)

for i in range(x):
    r,c = positions[i]
    if i==0:
        grid[r][c]='S'
    else:
        grid[r][c]='X'

print(n, m, ret)
[print("".join(row)) for row in grid]
