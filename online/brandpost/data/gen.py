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



maxN = int(cmdlinearg("maxN", 20000))
maxGridSize = int(cmdlinearg("maxSize", 1000))
n = int(cmdlinearg('n', random.randint(1,maxN)))
w = int(cmdlinearg("w", random.randint(1,maxGridSize)))
h = int(cmdlinearg("h", random.randint(1,maxGridSize)))
if w==h==1:
    h=2
if n>w*h:
    n = w*h - w*random.randint(0,1)

mode = cmdlinearg("mode", "")




hydrants = []
used = [[0]*(w+1) for _ in range(h+1)]
pool=[]

if mode == "leftPath": #Placera hydrants längs pathen på vänster sida
    pool = set()
    for i in range(1,w+1):
        pool.add((i,h))
    for j in range(1,h):
        pool.add((1,j))

    if len(pool)<n:
        n=len(pool)
        if random.randint(0,1):
            n//=2

    pool = list(pool)

elif mode == "rightPath": #Placera hydrants längs pathen på högersida sida
    pool = set()
    for i in range(1,w+1):
        pool.add((i,1))
    for j in range(1,h):
        pool.add((w,j))

    if len(pool)<n:
        n=len(pool)
        if random.randint(0,1):
            n//=2

    pool = list(pool)


elif mode == "edges" or mode == "weighted": #Hydrants är längs kanterna av rutnätet
    pool = set()
    for i in range(1,w+1):
        pool.add((i,h))
        pool.add((i,1))
    for j in range(1,h):
        pool.add((1,j))
        pool.add((w,j))
    
    if len(pool)<n and mode != "weighted":
        n=len(pool)
        if random.randint(0,1):
            n//=2
    
    pool = list(pool)


random.shuffle(pool)


if mode == "hydrantAtStart": #Group 1, endast start har hydrant
    hydrants.append((1,1))

while len(hydrants)<n:
    if mode == "weighted": 
        if len(pool) and random.randint(0,5) < 5:
            cand = pool.pop()
            if used[cand[1]][cand[0]]:
                continue
            hydrants.append(cand)
            used[cand[1]][cand[0]]=1
        else:
            cand=(random.randint(1,w),random.randint(1,h))
            if used[cand[1]][cand[0]]:
                continue
            hydrants.append(cand)
            used[cand[1]][cand[0]]=1
    else:
        if len(pool):
            cand = pool.pop()
            if used[cand[1]][cand[0]]:
                continue
            hydrants.append(cand)
            used[cand[1]][cand[0]]=1
        else:
            cand=(random.randint(1,w),random.randint(1,h))
            if used[cand[1]][cand[0]]:
                continue
            hydrants.append(cand)
            used[cand[1]][cand[0]]=1

print(w,h,n)
random.shuffle(hydrants)
for x,y in hydrants:
    print(x,y)


