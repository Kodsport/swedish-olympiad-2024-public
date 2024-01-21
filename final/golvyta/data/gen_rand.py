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

def get_rc(n,m,s):
    r = 0
    c = 0
    for ch in s:
        dx, dy = D[ch]
        r += dx
        c += dy
        r = max(0, r)
        r = min(n-1, r)
        c = max(0, c)
        c = min(m-1, c)
    return (r, c)

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

MAXN = 3*10**5

D = {'>': (0,1), '<': (0,-1), 'v': (1,0), '^': (-1,0)}
dirs = ['>', '<', 'v', '^']

length = int(cmdlinearg("n"))
mode = cmdlinearg("mode")

maxn = int(cmdlinearg("maxn", MAXN))
maxm = int(cmdlinearg("maxm", MAXN))

downright = int(cmdlinearg("downright", 0))

if downright == 1:
    dirs = ['>', 'v']

if mode == "random":
    L = []
    for _ in range(length):
        L.append(random.choice(dirs))
    r = random.randrange(0, maxn)
    c = random.randrange(0, maxm)
    s = "".join(L)
    print(length)
    print(s)
    print(r, c)
elif mode == "valid":
    n = maxn
    m = maxm
    L = []
    for _ in range(length):
        L.append(random.choice(dirs))
    s = "".join(L)
    r, c = get_rc(n, m, s)
    print(length)
    print(s)
    print(r, c) 


