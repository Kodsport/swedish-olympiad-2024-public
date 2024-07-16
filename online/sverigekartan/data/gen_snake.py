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
mode = cmdlinearg("mode", "")
print(r)
print(c)


matrix = [['.' for _ in range(c)] for _ in range(r)]

snake_coordinates = []

for i in range(r):
    row = []
    for j in range(c):
        if i % 2 == 0:
            matrix[i][j] = '#'
            row.append((i, j))
        elif i % 4 == 1 and j == c - 1:
            matrix[i][j] = '#'
            row.append((i, j))
        elif i % 4 == 3 and j == 0:
            matrix[i][j] = '#'
            row.append((i, j))
    
    if i%4==2:
        row = reversed(row)
    snake_coordinates.extend(row)

if mode=="update":
    del snake_coordinates[0]
    print(len(snake_coordinates))
    matrix = [['.' for _ in range(c)] for _ in range(r)]
else:
    print(0)

matrix[0][0] = 'S'

[print("".join(i)) for i in matrix]

if mode=="update":
    
    for coord in snake_coordinates:
        print(coord[0]+1, coord[1]+1)



