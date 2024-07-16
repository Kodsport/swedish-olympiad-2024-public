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
n = int(cmdlinearg('n'))
q = int(cmdlinearg('q'))
prob_right = float(cmdlinearg("prob_right"))
querymode = cmdlinearg("querymode")

print(n)
for i in range(n-1):
    if random.random() < prob_right:
        print(i+1,i+2)
    else:
        print(i+2,i+1)

print(q)
if querymode=="leftright":
    cnt = 0
    t = n
    for i in range(q):
        print(i+1,t)
        t-=1
elif querymode=="random":
    for i in range(q):
        u = random.randint(100, n-100)
        print(u,u+random.randint(-50,50))
else:
    print("ERROR UNKNOWN MODE")