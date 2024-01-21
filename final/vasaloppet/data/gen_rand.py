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
t = int(cmdlinearg("t"))
s = int(t*float(cmdlinearg("s_ratio")))
mode = cmdlinearg("mode", "random")

intervals = []

if mode == "random":
    sz = int(t/(n*3))
    last = 0
    for i in range(n):
        l = rand(last+1, last+1+sz)
        r = rand(l+1, l+1+sz)
        intervals.append((l,r))
        last = r
elif mode == "12":
    lengths = []
    for i in range(n):
        lengths.append(random.randint(1,2))
    gaps = random.sample(range(t-sum(lengths)-n), n)
    gaps.sort()
    prev = 0
    for i in range(n):
        g = gaps[i]
        if i > 0:
            g -= gaps[i-1]
        l = g+prev
        intervals.append((l, l+lengths[i]))
        prev = l+lengths[i]

print(n,t,s)
[print(l,r) for l,r in intervals]