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

t = int(2e5-10)
c=rand(int(9e8), int(1e9-10))

profits = []
costs = []
placed = 0
o = 1
for i in range(int(1e5)):
    profits.append(rand(1,int(1e9)))
    costs.append(int(1e9-5))

while len(costs) < t:
    profits.append(rand(1,int(1e9)))
    profits.append(rand(1,int(1e9)))
    costs.append(1)
    costs.append(c-o+1)
    o+=1


print(len(costs),c)
print(" ".join(str(i) for i in profits))
print(" ".join(str(i) for i in costs))


