#!/usr/bin/python3

n, k = map(int,input().split())
tree = [[] for _ in range(n)]

for i in range(n-1):
    a, b = map(int,input().split())
    a -= 1
    b -= 1
    tree[a].append(b)
    tree[b].append(a)

dist = [0] * n
par = [-1] * n

order = [0]

for i in order:
    for j in tree[i]:
        if j != par[i]:
            par[j] = i
            dist[j] = dist[i]+1
            order.append(j)

starts = [[] for _ in range(n)]
start = []
stop = []

for i in range(k):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    starts[a].append(i)
    start.append(a)
    stop.append(b)

indeg = [0] * k
dag = [[] for _ in range(k)]

for i in range(k):
    u, v = start[i], stop[i]
    if dist[u] > dist[v]:
        u, v = v, u
    path = []
    while dist[v] > dist[u]:
        path.append(v)
        v = par[v]
    while u != v:
        path.append(u)
        path.append(v)
        u = par[u]
        v = par[v]
    path.append(u)
    for p in path:
        for j in starts[p]:
            if j != i:
                indeg[i] += 1
                dag[j].append(i)

ans = []
for i in range(k):
    if indeg[i] == 0:
        ans.append(i)

for i in ans:
    for j in dag[i]:
        indeg[j] -= 1
        if indeg[j] == 0:
            ans.append(j)

if len(ans) == k:
    print("YES")
    for i in range(k):
        ans[i] += 1
    print(*ans)
else:
    print("NO")
