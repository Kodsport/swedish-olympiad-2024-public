#!/usr/bin/python3
import sys
sys.setrecursionlimit(100000+10)

n, k = [int(i) for i in input().split()]
p = [int(i) - 1 for i in input().split()]
children = [[] for i in range(n)]
for child, par in enumerate(p):
    children[par].append(child+1)

def dfs(node, guess):
    component_size = 1
    walls = 0

    for c in children[node]:
        csz, w = dfs(c, guess)
        component_size += csz
        walls += w
    
    if component_size > guess:
        component_size = 0
        walls += 1
    return component_size, walls

low = 0; high = n
while high - low > 1:
    mid = (low + high) // 2
    _, walls = dfs(0, mid)
    if walls <= k:
        high = mid
    else:
        low = mid
print(high)
