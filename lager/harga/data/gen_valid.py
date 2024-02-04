#!/usr/bin/python3

import sys
import random
from permutation import *

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
cycles = int(cmdlinearg("cycles", -1))

mode = cmdlinearg("mode", "random")

X = []
F = []

if mode == "random":
    p1 = list(range(m))
    random.shuffle(p1)
    pi = permutation(p1)
    sigma = pi.exponentiate(n)
    Y = []
    for i in range(len(sigma.cycles)):
        j = sigma.cycles[i][0]
        Y.append(j)
    while len(Y) < n:
        Y.append(random.randrange(m))
    
    for i in range(n):
        X.append(pi.step(Y[i], -i))
    for i in range(m):
        F.append(p1[i]+1)
    for i in range(n):
        X[i] += 1

elif mode == "cycles":
    pi = get_permutation(m, cycles)
    sigma = pi.exponentiate(n)
    Y = []
    for i in range(len(sigma.cycles)):
        j = sigma.cycles[i][0]
        Y.append(j)
    while len(Y) < n:
        y = random.choice(Y)
        Y.append(y)

    for i in range(n):
        X.append(pi.step(Y[i], -i))
    for i in range(m):
        F.append(pi.p[i]+1)
    for i in range(n):
        X[i] += 1

elif mode == "unicycle":
    pi = get_permutation(m, 1)
    sigma = pi.exponentiate(n)
    Y = random.sample(range(m), cycles)
    while len(Y) < n:
        y = random.choice(Y)
        Y.append(y)
        
    for i in range(n):
        X.append(pi.step(Y[i], -i))
    for i in range(m):
        F.append(pi.p[i]+1)
    for i in range(n):
        X[i] += 1

elif mode == "equal_cycles" or mode == "equal_cycles_random":
    m -= m%cycles
    pi = equal_cycles(m // cycles, cycles)
    sigma = pi.exponentiate(n)
    Y = []
    for i in range(n):
        j = i%len(sigma.cycles)
        Y.append(sigma.cycles[j][0])
    for i in range(cycles):
        Y[n-cycles+i] = sigma.cycles[i][0] # last should be in same order as first
    if mode == "equal_cycles_random":
        random.shuffle(Y)
    for i in range(n):
        X.append(pi.step(Y[i], -i))
    for i in range(m):
        F.append(pi.p[i]+1)
    for i in range(n):
        X[i] += 1


print(n,m)
print(*X)
print(*F)


