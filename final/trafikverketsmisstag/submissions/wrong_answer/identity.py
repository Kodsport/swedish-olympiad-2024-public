#!/usr/bin/python3

n, k = map(int,input().split())
tree = [[] for _ in range(n)]

for i in range(n-1):
    a, b = map(int,input().split())
    a -= 1
    b -= 1
    tree[a].append(b)
    tree[b].append(a)

edges = []
for _ in range(k):
    start, stop = map(int, input().split())
    start -= 1
    stop -= 1
    edges.append((start, stop))

print("YES")
print(*list(range(1,k+1)))
