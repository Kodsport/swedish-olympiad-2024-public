#!/usr/bin/python3
n,m,r = [int(x) for x in input().split()]
grid = [input() for _ in range(n)]

k = 0
for row in grid:
    for c in row:
        k += c != '.'

# Make a graph out of crosses
from collections import defaultdict
indexer = defaultdict(lambda:len(indexer))
direction = {}

graph = [[] for _ in range(k)]
for i in range(n):
    for j in range(m):
        if grid[i][j] != '.':
            ind = indexer[i,j]

            direction[ind, ind] = ''

            for di,dj,d in (-1,0,'^'),(1,0,'v'),(0,-1,'<'),(0,1,'>'):
                ii = i + di
                jj = j + dj
                while 0<=ii<n and 0<=jj<m and grid[ii][jj] == '.':
                    ii += di
                    jj += dj
                if 0<=ii<n and 0<=jj<m:
                    ind2 = indexer[ii, jj]
                    graph[ind].append(ind2)
                    direction[ind, ind2] = d

for si in range(n):
    for sj in range(m):
        if grid[si][sj] == 'S':
            break
    else:
        continue
    break
sind = indexer[si, sj]


# Construct a spanning tree with a BFS
P = [-1] * k
BFS = [sind]
P[sind] = -2
for u in BFS:
    for v in graph[u]:
        if P[v] == -1:
            P[v] = u
            BFS.append(v)

if len(BFS) < k:
    print(-1)
    exit()

path = []
color = [1] * k

# Parity fix
if k&1 and r==1:

    # Find odd cycle (if it exists)
    dist = [0] * k
    for u in BFS[1:]:
        dist[u] = dist[P[u]] + 1
    
    odd_path = []
    for u in range(k):
        for v in graph[u]:
            if dist[u] == dist[v]:
                while u != sind:
                    odd_path.append(u)
                    u = P[u]
                odd_path.append(sind)
                odd_path.reverse()
                while v != sind:
                    odd_path.append(v)
                    v = P[v]
                break
        else:
            continue
        break

    if not odd_path:
        # No odd cycle exists
        print(-1)
        exit()
    
    for u in odd_path:
        color[u] ^= 1

    odd_path.append(sind)
    path += odd_path

# Edges can be used twice or 4 times.
# This walk will convert all remaining crosses into circles
count = [0] * k
for u in BFS[::-1]:
    if P[u] >= 0:
        if color[u] == 1:
            count[u] = 2

            color[u] ^= 1
            color[P[u]] ^= 1
        else:
            count[u] = 4

stack = [sind]
while stack:
    u = stack.pop()
    if u >= 0:
        path.append(u)
        stack.append(~u)
        for v in graph[u]:
            if P[v] == u:
                stack.append(v)
    else:
        u = ~u
        if P[u] >= 0:
            path.append(P[u])
            if count[u] == 4:
                path.append(u)
                path.append(P[u])

if color[sind] and r==0:
    path.pop()
    color[sind] ^= 1

assert all(c == 0 for c in color)
assert r==0 or path[0] == sind

S = [direction[path[i], path[i + 1]] for i in range(len(path) - 1)]
S = ''.join(S)

print(len(S))
print(S)
