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

branches = int(cmdlinearg('branches', 5))
onlyRight = int(cmdlinearg('onlyRight', 0))
bounded = int(cmdlinearg("bounded", 0))

print(n,k)


positions = []
if bounded:
    positions = random.sample([*range(0,(2*10**5)-10,3)],n)
else:
    used = set()
    while len(positions) < n:
        cand = random.randint(0,10**9-1)
        if cand in used:
            continue
        used.add(cand)
        positions.append(cand)

positions.sort()

print(*positions)

print(*[branches]*n)

prevHeights = []

for i in range(n):
    heights = []
    lengths = []

    while len(heights)<branches:
        h = random.randint(1,10**9)
        if h in prevHeights or h in heights:
            continue

        if i == 0:
            lower = -1
        else:
            lower = positions[i-1]
        
        if i == n-1:
            upper = [10**9,positions[-1]+10**5][bounded]
        else:
            upper = min([10**9,positions[-1]+10**5][bounded],positions[i+1])
        
        cands = []
        if positions[i]-lower > 1 and not onlyRight:
            cands.append(-random.randint(1,positions[i]-lower-1))
        if upper - positions[i] > 1:
            cands.append(random.randint(1, upper-positions[i]-1))
        
        random.shuffle(cands)
        
        heights.append(h)
        lengths.append(cands[0])

    print(*heights)
    print(*lengths)   

    prevHeights,heights = heights,prevHeights   
    

