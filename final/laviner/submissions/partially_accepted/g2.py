#!/usr/bin/python3

n, k = map(int, input().split())
parents = [0]+[*map(int, input().split())]
for i in range(n):
    parents[i] -= 1
edges = [[] for _ in range(n)]
for i,x in enumerate(parents):
    if i == 0:
        continue
    edges[i].append(x)
    edges[x].append(i) 

cands = []
for blocked in range(n):
    best = 0
    visited = [0]*n
    visited[blocked] =1
    for start in range(n):
        if visited[start]:
            continue
        BFS = [start]
        visited[start] = 1
        for curr in BFS:
            for nei in edges[curr]:
                if visited[nei]:
                    continue
                BFS.append(nei)
                visited[nei]=1
  
        best = max(len(BFS),best)
    
    cands.append(best)

print(min(cands))

