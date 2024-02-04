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

mode = cmdlinearg("mode")

profits = []
costs = []
if mode == "random":
    for _ in range(n):
        profits.append(rand(1,int(1e9)))
        costs.append(rand(1,c))
elif mode=="manysmall":
    for _ in range(n):
        profits.append(rand(1,int(1e9)))
        costs.append(rand(1,200))
elif mode=="increasing":
    last = 1
    delta = int(cmdlinearg("delta", c//int(n*1.5)))

    for _ in range(n):
        profits.append(rand(1,int(1e9)))
        next = rand(last, last+delta)
        costs.append(next)
        last = next
elif mode=="randomweight":
    for _ in range(n):
        profits.append(rand(1,int(1e9)))
        costs.append(rand(1,int(1e9)))
else:
    assert 0, f"Unknown mode {mode}"

print(n,c)
print(" ".join(str(i) for i in profits))
print(" ".join(str(i) for i in costs))


