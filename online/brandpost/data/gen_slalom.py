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




maxGridSize = int(cmdlinearg("maxSize", 1000))

w = int(cmdlinearg("w", random.randint(1,maxGridSize)))
h = int(cmdlinearg("h", random.randint(1,maxGridSize)))

slalomDist = int(cmdlinearg("dist", w//10)) #distance between the slalom sticks
slalomLength = int(cmdlinearg("length", h//2)) #length of the slalom sticks

mode = cmdlinearg("mode", "")

hydrants = set()
used = [[0]*w for _ in range(h)]

bottom=0

if slalomDist==0:
    slalomDist=w//3
for i in range(slalomDist,w+1,slalomDist):
    bottom=1-bottom
    if bottom:
        for j in range(1,slalomLength+1):
            if j>h:
                break
            hydrants.add((i,j))
    else:
        for j in range(h,h-slalomLength-1,-1):
            if j<1:
                break
            hydrants.add((i,j))


hydrants=list(hydrants)

random.shuffle(hydrants)

n = int(cmdlinearg('n', len(hydrants)))
if n>len(hydrants):
    n=len(hydrants)

if mode=="transposed":
    print(h,w,n)

    for x,y in hydrants[:n]:
        print(y,x)

else:
    print(w,h,n)

    for x,y in hydrants[:n]:
        print(x,y)


