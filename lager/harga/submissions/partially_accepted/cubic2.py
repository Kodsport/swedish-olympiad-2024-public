#!/usr/bin/python3

n,m = map(int, input().split())

starts = [*map(lambda x: int(x)-1, input().split())]

next = [*map(lambda x: int(x)-1, input().split())]


grid = [[0]*n for _ in range(n*m+1)]

grid[0] = starts

for t in range(1,n*m+1):
    for i in range(n):
        if i == n-1:
            i = -1
        grid[t][i] = next[grid[t-1][i+1]]

output = [0]*n

for i in range(n):
    visited = [0]*m
    count = 0
    for t in range(n*m+1):
        if not visited[grid[t][i]]:
            visited[grid[t][i]] = 1
            count += 1
        if count == m:
            break
    if count != m:
        print(-1)
        exit()
    else:
        output[i] = t+1

print(*output)
