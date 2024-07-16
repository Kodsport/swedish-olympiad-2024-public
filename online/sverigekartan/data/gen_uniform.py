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
r = int(cmdlinearg('r'))
c = int(cmdlinearg('c'))
q = int(cmdlinearg('q'))
d = float(cmdlinearg('density'))
print(r)
print(c)

grid = [['.' for i in range(c)] for j in range(r)]

num_land = int(r*c*d)
all_positions = [(i,j) for j in range(c) for i in range(r)]
land_positions = random.sample(all_positions, num_land)

for p in land_positions:
    grid[p[0]][p[1]] = '#'

grid[random.randint(0,r-1)][random.randint(0,c-1)] = 'S'

iswater = [(i,j) for i in range(r) for j in range(c) if grid[i][j]=='.']
random.shuffle(iswater)

queries = []

while len(iswater) and q:
    queries.append(iswater[-1])
    del iswater[-1]
    q-=1

print(len(queries))
[print("".join(i)) for i in grid]
for i in queries:
    print(i[0]+1,i[1]+1)