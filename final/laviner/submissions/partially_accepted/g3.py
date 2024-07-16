#!/usr/bin/python3
from itertools import combinations

n, k = map(int, input().split())
parents = [0]+[*map(int, input().split())]
edges = [[] for _ in range(n)]
for i,x in enumerate(parents[1:]):
    edges[x-1].append(i+1)
for i in range(n):
    parents[i] -= 1

nodeCands = [*range(n)]
nodeCands.sort(key = lambda x: len(edges[x]))

cands = []
for comb in combinations([*range(n)],k):
    walled = [0]*n

    for node in comb:
        walled[node] = 1

    best = 0
    for start in range(n):
        if walled[start]:
            continue
        BFS = [start]
        walled[start] = 1
        for curr in BFS:
            for nei in edges[curr]:
                if walled[nei]:
                    continue
                BFS.append(nei)
                walled[nei]=1

        best = max(len(BFS),best)
    cands.append(best)

print(min(cands))
