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
fill = int(cmdlinearg('fill',0))

grid = [["."]*m for _ in range(n)]

x = y = 0
if random.randint(0,1) or fill:
    grid[x][y] = chr(random.randint(ord("a"),ord("z")))

while x!=n-1 or y!=m-1:
    if random.randint(0,1):
        dx,dy=0,1
    else:
        dx,dy=1,0
    
    if 0<=x+dx<n and 0<=y+dy<m:
        if random.randint(0,1) or fill:
            grid[x+dx][y+dy] = chr(random.randint(ord("a"),ord("z")))
        x+=dx
        y+=dy

if random.randint(0,1) or fill:
    grid[x][y] = chr(random.randint(ord("a"),ord("z")))

dots = 0
for x in grid:
    dots += x.count(".")
if dots == n*m:
    grid[0][0] = chr(random.randint(ord("a"),ord("z")))

print(n,m)
for x in grid:
    print("".join(x))

