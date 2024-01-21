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

edges = []
p = 0
last = 0
while p+2 < n*0.9:
    edges.append((p+1,p+2))
    last = p+2
    p+=1

while len(edges) < n-1:
    edges.append((randint(int(last*0.9),p+1), p+2))
    p+=1



people = []
l = n//2
r = l+2
while l >= 1 and r <= n:
    people.append((l, r))
    people.append((r, l+1))
    l-=1
    r+=1

# Shuffle node labels for extra cache misses 🤤
nodes = set(node for edge in edges for node in edge)

shuffled_nodes = list(nodes)
random.shuffle(shuffled_nodes)

node_mapping = dict(zip(nodes, shuffled_nodes))

edges = [(node_mapping[edge[0]], node_mapping[edge[1]]) for edge in edges]
people = [(node_mapping[p[0]], node_mapping[p[1]]) for p in people]


random.shuffle(edges)
random.shuffle(people)
print(n,len(people))
for e in edges:
    print(e[0],e[1])
for p in people:
    print(p[0],p[1])