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

n = int(cmdlinearg("n"))
mode = cmdlinearg("mode")
p1 = float(cmdlinearg("p1", 0.0))
start = int(cmdlinearg("start", 0))

maxn = int(cmdlinearg("maxn", -1))
if maxn == -1:
    maxn = random.randint(1, MAXN)

if mode == "onedirection":
    s = [dirs[start]] * n
    k = int(p1 * n)
    for i in range(k):
        s[i] = dirs[random.randint(0,1)]
        s[n-i-1] = dirs[random.randint(0,1)]
    print(n)
    print("".join(s))
    r, c = get_rc(1,maxn,s)
    print(r, c)
elif mode == "backandforth":
    n1 = int(p1 * n)
    n2 = n-n1
    s = [dirs[0]]*n1 + [dirs[1]]*n2
    print(n)
    print("".join(s))
    r, c = get_rc(1,maxn,s)
    print(r, c)
elif mode == "chunks":
    s = [start]
    for i in range(1, n):
        if random.random() < p1:
            s.append((s[-1]^1))
        else:
            s.append(s[-1])
    for i in range(n):
        s[i] = dirs[s[i]]
    print(n)
    print("".join(s))
    r, c = get_rc(1,maxn,s)
    print(r, c)
    


