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

w=h=maxGridSize

maxN = int(cmdlinearg("maxN",20000))

plankWidth = int(cmdlinearg("width", w//5)) #planka width
plankLength = int(cmdlinearg("height", random.randint(3,4)*h//5)) #planka height

mode = cmdlinearg("mode", "")

hydrants = []
used = [[0]*(w+1) for _ in range(h+1)]



for i in range(plankWidth+1,w+1,plankWidth*4):
    
    for di in range(0,plankWidth):

        for j in range(1,plankLength+1):
            if 1<=i+di<=w and 1<=j<=h:
                if used[i+di][j]:
                    continue

                hydrants.append((i+di,j))
                used[i+di][j]=1

for i in range(3*plankWidth+1,w+1,plankWidth*4):
    
    for di in range(0,plankWidth):

        for j in range(h+1,h-plankLength-1,-1):
            if 1<=i+di<=w and 1<=j<=h:

                if used[i+di][j]:
                    continue

                hydrants.append((i+di,j))
                used[i+di][j]=1


random.shuffle(hydrants)

n = min(len(hydrants),maxN)

if mode=="transposed":
    print(h,w,n)

    for x,y in hydrants[:n]:
        print(y,x)

else:
    print(w,h,n)

    for x,y in hydrants[:n]:
        print(x,y)


