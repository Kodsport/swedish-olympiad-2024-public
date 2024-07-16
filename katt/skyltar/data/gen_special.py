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
m = int(cmdlinearg('m'))

R = int(cmdlinearg('r',0))
print(n,m)

for i in range(n):
    r = random.randint(1,750000)
    if R:
        
        temp = [500000]*(m-min(m,i)) + [750000]*min(m,i)
    else:
        temp = [r]*(m-min(m,i)) + [r+1]*min(m,i)
    print(*temp)

