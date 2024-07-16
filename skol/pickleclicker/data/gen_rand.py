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
t = int(cmdlinearg("t"))
p = int(cmdlinearg("p"))

print(n,t)
[print(random.randint(1, p), random.randint(1,t)) for i in range(n)]

