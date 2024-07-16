#!/usr/bin/python3

import sys
import random
import math
from random import randint

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
q = int(cmdlinearg('q'))
querymode = cmdlinearg("querymode")

# Trees have logarithmic height

# Stolen from https://github.com/cheran-senthil/PyRival/blob/master/pyrival/data_structures/DisjointSetUnion.py
class UF:
    def __init__(self, n):
        self.parent = list(range(n))

    def find(self, a):
        acopy = a
        while a != self.parent[a]:
            a = self.parent[a]
        while acopy != a:
            self.parent[acopy], acopy = a, self.parent[acopy]
        return a

    def union(self, a, b):
        self.parent[self.find(b)] = self.find(a)

print(n)
uf = UF(n)

for i in range(n-1):
    while True:
        a,b=randint(0,n-1),randint(0,n-1)
        if uf.find(a)==uf.find(b):continue
        uf.union(a,b)
        print(f"{a+1} {b+1}")
        break

print(q)
if querymode=="random":
    for i in range(q):
        print(randint(1,n), randint(1,n))
elif querymode=="samegoal":
    for i in range(q):
        print(randint(1,n), 1)
else:
    assert False, f"Unknwon mode {querymode}"
