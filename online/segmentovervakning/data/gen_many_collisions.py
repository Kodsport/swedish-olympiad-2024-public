#!/usr/bin/python3

import sys
import random
import math
import heapq
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
unique = int(cmdlinearg("unique", 2))
rem_prob = float(cmdlinearg("rem", 0.0))
sub2 = cmdlinearg("sub2", "no")

MAXX = 10**9
id_hi= 10**6
ids = [i+1 for i in range(int(id_hi))]
random.shuffle(ids)

active = []

X = random.sample(range(1, MAXX+1), unique)
X.sort()
x_min = X[0]
x_max = X[-1]

print(x_min, x_max)
print(q)

i = 0
while i < q:
    if len(active) > 0 and random.random() < rem_prob:
        id = heapq.heappop(active)
        print("-", id)
        q -= 1
    else:
        id = ids[i]
        r = random.randint(1, 3)
        if sub2 == "yes":
            if r == 1:
                lo = random.randrange(1, x_min)
                hi = random.randrange(1, x_min)
            elif r == 2:
                lo = random.randint(x_max+1, MAXX)
                hi = random.randint(x_max+1, MAXX)
            else:
                lo = x_min
                hi = x_max
        else:
            if r == 1:
                lo = random.randrange(1, x_min)
                hi = X[random.randint(0, len(X)-2)]
            elif r == 2:
                lo = X[random.randint(1, len(X)-1)]
                hi = random.randint(x_max+1, MAXX)
            else:
                lo = random.choice(X)
                hi = random.choice(X)
        if lo > hi:
            lo, hi = hi, lo
        elif lo == hi:
            continue
        heapq.heappush(active, id)
        print("+", id, lo, hi)
        i += 1
