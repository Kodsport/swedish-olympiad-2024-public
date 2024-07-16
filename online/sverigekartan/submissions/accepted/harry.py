#!/usr/bin/env python3

r = int(input())
c = int(input())
u = int(input())

grid = [[*input()] for _ in range(r)]



for y in range(r):
    for x in range(c):
        if grid[y][x] == "S":
            start=(x,y)


out = 1
visited = [[0]*c for _ in range(r)]
visited[start[1]][start[0]]=1

def doBFS(start):
    BFS=[start]
    newLand=0
    for x,y in BFS:
        for dx,dy in [(0,1),(0,-1),(1,0),(-1,0)]:
            if 0<=x+dx<=c-1 and 0<=y+dy<=r-1:
                if visited[y+dy][x+dx]:
                    continue
                if grid[y+dy][x+dx]=="#":
                    visited[y+dy][x+dx]=1
                    BFS.append((x+dx,y+dy))
                    newLand+=1
    return newLand

out += doBFS(start)
print(out)

for _ in range(u):
    y,x = map(int,input().split())
    x-=1
    y-=1
    grid[y][x]="#"
    for dx,dy in [(0,1),(0,-1),(1,0),(-1,0)]:
            if 0<=x+dx<=c-1 and 0<=y+dy<=r-1:
                if visited[y+dy][x+dx]:
                    visited[y][x]=1
                    out += 1 
                    out += doBFS((x,y))
                    break
    print(out)
    #print(visited)