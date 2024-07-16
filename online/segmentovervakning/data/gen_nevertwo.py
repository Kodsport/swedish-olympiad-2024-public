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
w = int(cmdlinearg("addweight"))

lo = 12345
hi = 56789
assert hi > lo

print(lo,hi)
print(q)

id_hi=10**6#int(1e6)
ids = [i+1 for i in range(int(id_hi))]
random.shuffle(ids)

cnt = 0
while cnt < q//2: # Random junk for half of it
    id = ids[-1]
    del ids[-1]
    print("+", id, randint(1, lo), randint(lo+1,(lo+hi)//4*3))
    cnt+=1

coversall = []
while cnt < q:
    if randint(0, w) or len(coversall)==0:
        id = ids[-1]
        del ids[-1]
        print("+", id, randint(1,lo), randint(hi, int(1e9)))
        coversall.append(id)
    else:
        u = coversall[-1]
        del coversall[-1]
        print("-", u)
    cnt+=1
