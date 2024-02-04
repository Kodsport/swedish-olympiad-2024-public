#!/usr/bin/python3

import sys
import random

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default


random.seed(int(cmdlinearg('seed', sys.argv[-1])))

MAXN = 3*10**5

n = int(cmdlinearg("n"))
m = int(cmdlinearg("m"))

mode = cmdlinearg("mode", "random")

X = []
F = list(range(1,m+1))

if mode == "random":
    for i in range(n):
        X.append(i%m+1)
    random.shuffle(X)

elif mode == "sorted":
    for i in range(n):
        X.append(i%m+1)
    X.sort()

elif mode == "cycle1":
    for i in range(n):
        X.append(i%m+1)

elif mode == "cycle2":
    while len(X) < n:
        temp = list(range(1,m+1))
        random.shuffle(temp)
        X += temp
    while len(X) > n:
        X.pop()

print(n,m)
print(*X)
print(*F)

