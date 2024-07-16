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

q = int(cmdlinearg("q"))
mode = cmdlinearg("mode")

lo = 12345
hi = 56789
assert hi > lo

print(lo,hi)
print(q)

id_hi=10**6#int(1e6)
ids = [i+1 for i in range(int(id_hi))]
random.shuffle(ids)

if mode=="random": # weak
    import heapq
    intervals = []
    removeratio = int(cmdlinearg("remratio",1))

    for i in range(q):
        if randint(0,1) or len(intervals)==0:
            id = ids[-1]
            del ids[-1]
            heapq.heappush(intervals, (randint(1,1000), id))
            l = randint(lo//2, hi*2-1)
            r = randint(l+1, hi*2)
            assert r>l
            print("+", id, l,r)
        else:
            u = heapq.heappop(intervals)
            print("-", u[1])
elif mode=="harder":
    cnt = 0
    while cnt < q//2:
        id = ids[-1]
        del ids[-1]
        print("+", id, randint(1, lo), randint(lo+1,(lo+hi)//4*3))
        cnt+=1
    while cnt < q:
        id = ids[-1]
        del ids[-1]
        print("+", id, randint(lo+1,(lo+hi)//4*3), randint(hi+1, int(1e9)))
        cnt+=1
        if cnt<q:
            print("-", id)
            cnt+=1
else:
    print("ERROR")


