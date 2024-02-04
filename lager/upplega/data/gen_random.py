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
k = int(cmdlinearg('k'))
dist = int(cmdlinearg('dist', 10))
branches = int(cmdlinearg('branches', 5))

onlyRight = int(cmdlinearg('onlyRight', 0))

print(n,k)

print(*range(dist,dist*(n+1),dist))
print(*[branches]*n)

grenar = [(i,(-1)**random.randint(0,1-onlyRight)*random.randint(1,dist-1)) for i in range(1,1+n*branches)]
random.shuffle(grenar)
for _ in range(n):
    heights = []
    lengths = []
    for _ in range(branches):
        h,l = grenar.pop()
        heights.append(h)
        lengths.append(l)

    print(*heights)
    print(*lengths)        
    

