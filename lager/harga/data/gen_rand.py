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

mode = cmdlinearg("mode", "random")

X = []
F = []

if mode == "random":
    # probably will lead to all -1s
    for _ in range(n):
        X.append(random.randint(1,m))
    for _ in range(m):
        F.append(random.randint(1,m))

elif mode == "permutation":
    for _ in range(n):
        X.append(random.randint(1,m))
    for i in range(m):
        F.append(i+1)
    random.shuffle(F)

elif mode == "identity":
    for _ in range(n):
        X.append(random.randint(1,m))
    for i in range(m):
        F.append(i+1)

elif mode == "chain":
    C = random.sample(range(0, m), chain)
    chained = [0] * m
    for c in C:
        chained[c] = 1
    P = []
    for i in range(m):
        if chained[i] == 0:
            P.append(i)
        F.append(-1)
    random.shuffle(P)

    for i in range(len(C)-1):
        F[C[i]] = C[i+1]
    F[C[-1]] = P[0]

    p = 0
    for i in range(m):
        if chained[i] == 0:
            F[i] = P[p]
            p += 1

    for i in range(m):
        F[i] += 1
    for i in range(n//2):
        X.append(C[0]+1)
    for i in range(n//2, n):
        X.append(random.randint(1,m))

print(n,m)
print(*X)
print(*F)


