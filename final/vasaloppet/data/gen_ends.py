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
s_ratio = float(cmdlinearg("s_ratio",0.5))
s = int(t*s_ratio)

endSize = int(cmdlinearg("endSize"))

mode = cmdlinearg("mode", "end")

intervals = []

assert mode in ["end", "begin"]

if mode == "begin":
    intervals.append((0,int(endSize)))
    last = intervals[-1][-1]
    sz = int((t-endSize)/(n*3))
    for i in range(n-1):
        l = rand(last+1, last+1+sz)
        r = rand(l+1, l+1+sz)
        intervals.append((l,r))
        last = r

elif mode == "end":
    rend = t
    lend = t-int(endSize)

    last = 0
    sz = int((t-endSize)/(n*3))
    for i in range(n-1):
        l = rand(last+1, last+1+sz)
        r = rand(l+1, l+1+sz)
        intervals.append((l,r))
        last = r
    intervals.append((lend,rend))
    

print(n,t,s)
[print(l,r) for l,r in intervals]