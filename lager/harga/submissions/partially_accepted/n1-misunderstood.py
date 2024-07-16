#!/usr/bin/python3

n,m = map(int, input().split())

starts = [*map(lambda x: int(x)-1, input().split())]

next = [*map(lambda x: int(x)-1, input().split())]

output = [-1]*n

for i in range(n):
    curr = starts[i]
    visited = [0]*m

    visited[curr] = 1
    time = 1
    while not visited[next[curr]]:
        curr = next[curr]
        time += 1
        visited[curr] = 1
    
    if sum(visited) == m:
        output[i] = time
    else:
        print(-1)
        exit()

print(*output)

