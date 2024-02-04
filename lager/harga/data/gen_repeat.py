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
chain = int(cmdlinearg("chain", 0))

mode = cmdlinearg("mode", "valid")

X = []
F = [-1] * m

inds = list(range(m))
random.shuffle(inds)

extra = 0
if mode == "disconnected":
    F[inds[-1]] = inds[-1]
    extra = 1

for i in range(m-extra):
    if i == m-1-extra:
        F[inds[i]] = inds[chain]
    else:
        F[inds[i]] = inds[i+1]

if mode == "invalid":
    X = [F[inds[0]]] * n
else:
    X = [inds[0]] * n

for i in range(n):
    X[i] += 1
for i in range(m):
    F[i] += 1

print(n,m)
print(*X)
print(*F)

