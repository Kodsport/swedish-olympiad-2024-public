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
x = int(cmdlinearg('x'))
y = int(cmdlinearg('y'))
hi=int(cmdlinearg("hi"))

print(n)
print(x)
print(y)
print(" ".join(str(randint(1,hi)) for i in range(n)))
