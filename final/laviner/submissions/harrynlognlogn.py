#!/usr/bin/python3

#O(nlog(n)^2)

import heapq

n, k = map(int, input().split())

parents = [0]+[*map(int, input().split())]

edges = [[] for _ in range(n)]

for i,x in enumerate(parents[1:]):
    edges[x-1].append(i+1)

for i in range(n):
    parents[i] -= 1

BFS = [0]
depth = [-1]*n
leaf = []

depth[0] = 0

for curr in BFS:
    if len(edges[curr]):
        for nei in edges[curr]:
            depth[nei] = depth[curr] + 1
            BFS.append(nei)
    else:
        heapq.heappush(leaf, (-depth[curr],curr))

def solve(m):
    #Can Joshua stop me from getting more than a score of m using less than k+1 walls?
    wallsUsed = 0
    size = [1]*n
    queue = leaf[:]
    visited = [0]*n

    #Trying greedy from the bottom
    while queue:
        d,curr = heapq.heappop(queue)
        visited[curr] = 1

        if size[curr] >= m:
            wallsUsed += 1
            size[curr] = 0
        
        if curr == 0:
            break
        
        size[parents[curr]] += size[curr]
        if not visited[parents[curr]]:
            heapq.heappush(queue, (d+1, parents[curr]))
            visited[parents[curr]] = 1
    
    if wallsUsed > k:
        return 1 #Joshua can't. Joshua has to use more than K walls to stop you from having m or more points. 
    return 0 #Joshua can.

l = 1
r = n-k

while l<r:
    m = -(-(l+r)//2) #ceil((l+r)/2)

    if solve(m):
        l = m
    else:
        r = m-1
        
print(l)
