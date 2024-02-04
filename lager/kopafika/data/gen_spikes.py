#!/usr/bin/python3

import sys
import random
rand = random.randint

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default


random.seed(int(cmdlinearg('seed', sys.argv[-1])))


n = int(cmdlinearg("n"))
c = int(cmdlinearg("c"))


profits = []
costs = []
for i in range(n):
    profits.append(rand(1,int(1e9)))
    if i%2==0:
        costs.append(rand(1,10))
    else:
        costs.append(rand(c*9//10, c))

print(n,c)
print(" ".join(str(i) for i in profits))
print(" ".join(str(i) for i in costs))


