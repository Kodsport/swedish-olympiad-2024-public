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
c = int(cmdlinearg('c'))
assert c<=n

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

uf = UF(n)

print(n, c)
for i in range(n-1):
    while True:
        a,b=randint(0,n-1),randint(0,n-1)
        if a==b:continue
        if uf.find(a)==uf.find(b):continue
        uf.union(a,b)
        print(a+1,b+1)
        break

startorder = [i+1 for i in range(n)]
random.shuffle(startorder)
for i in range(c):
    print(startorder[i],randint(1,n))
