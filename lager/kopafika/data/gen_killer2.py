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

c=rand(int(9e8), int(1e9))
halfn = int(1e5)
profits = []
costs = []
placed = 0
for i in range(halfn):
    profits.append(rand(1,int(1e9)))
    costs.append(1)

profits.append(rand(1,int(1e9)))
costs.append(c-halfn-20)

largest = c-(c-halfn-20)
while largest>1:
    profits.append(rand(1,int(1e9)))
    largest //= 2
    costs.append(largest)


while len(costs) < halfn*2:
    profits.append(rand(1, int(1e9)))
    costs.append(1000+rand(1,200))

print(halfn*2,c)
print(" ".join(str(i) for i in profits))
print(" ".join(str(i) for i in costs))


