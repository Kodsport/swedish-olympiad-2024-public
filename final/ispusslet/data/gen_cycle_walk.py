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
r = int(cmdlinearg('r'))
row = int(cmdlinearg('row'))
parity = int(cmdlinearg("p"))
n = int(cmdlinearg("n"))
m = int(cmdlinearg("m", n))
#randint(1,int(cmdlinearg("maxx")))
grid = [['.' for i in range(m)] for j in range(n)]

m-=4
i = 0
while i < m:
    grid[0][i]='X'
    i+=2

i = 1
while i < m:
    grid[row][i]='X'
    i+=2

for i in range(1,row):
    if i%2==0:
        grid[i][0]='X'
    else:
        grid[i][m-1]='X'
grid[row][0]='X'
grid[row][m-1]='X'
grid[0][m-1]='X'
grid[0][0]='X'

m+=4
i = n-1
while i >=row:
    grid[i][m-1]='X'
    i-=1
grid[n-1][m-1]='S'
if parity:
    grid[n-1][m-2]='X'

print(n, m, r)
[print("".join(row)) for row in grid]
