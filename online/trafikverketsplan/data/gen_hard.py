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

def shuffle_nodes(edgelist, star1, star2):
    nodes = list(set(node for edge in edgelist for node in edge))

    # Generate a mapping from old labels to new labels
    label_mapping = {old_label: new_label for old_label, new_label in zip(nodes, random.sample(nodes, len(nodes)))}

    # Apply the label mapping to the edges
    shuffled_graph = [(label_mapping[u], label_mapping[v]) for u, v in edgelist]
    star1 = [label_mapping[u] for u in star1]
    star2 = [label_mapping[u] for u in star2]

    return (shuffled_graph, star1,star2)


print(n)
n-=1
cnt = 0
root = 1
tail = -1
i = 1
edgelist = []
# Long line graph 33%
while cnt < n//3:
    edgelist.append((i+1,i))
    tail = i+1
    i+=1
    cnt+=1

star1 = []
# Star graph at bottom 33%
while cnt<n//3*2:
    edgelist.append((i+1,tail))
    star1.append(i+1)
    i+=1
    cnt+=1

# Extra random edges into bottom star 10%
for j in range(n//10):
    u = random.choice(star1)
    if randint(1,100)==1:
        edgelist.append((u, i+1))
    else:
        edgelist.append((i+1, u))
    star1.append(i+1)
    i+=1
    cnt+=1

star2 = []
# Star graph at top 23%
while cnt < n:
    edgelist.append((root, i+1))
    star2.append(i+1)
    i+=1
    cnt+=1

edgelist,star1,star2=shuffle_nodes(edgelist,star1,star2)

random.shuffle(edgelist)

for i in edgelist:
    print(i[0],i[1])

print(q)
for i in range(q):
    print(random.choice(star1), random.choice(star2))