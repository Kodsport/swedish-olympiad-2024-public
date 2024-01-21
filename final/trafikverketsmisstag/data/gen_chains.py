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
chainlength = int(cmdlinearg("len"))

edges = []
root = 1
prev = root
p = 2
l = 0
target = root
people = []

while p < n+1:
    edges.append((prev,p))
    people.append((p,target))
    prev = p
    p+=1
    l+=1
    if l>=chainlength:
        l=0
        target=prev
        prev=root


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