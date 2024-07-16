#!/usr/bin/env python3
r=int(input())
c=int(input())
q=int(input())
rows = [[j for j in input()] for i in range(r)]

spos = [-1,-1]
for i in range(r):
    for j in range(c):
        if rows[i][j]=='S':
            spos = [i,j]

dirs = [[0,1],[0,-1],[1,0],[-1,0]]

def floodfill():
    ans = 0
    q = []
    q.append(spos)
    vis = set()
    while len(q):
        u = q[-1]
        del q[-1]

        if tuple(u) in vis:
            continue
        vis.add(tuple(u))

        ans += 1

        for dir in dirs:
            np = [u[0]+dir[0], u[1]+dir[1]]
            if np[0]<0 or np[1]<0 or np[0]>=r or np[1]>=c or rows[np[0]][np[1]]=='.':
                continue
            q.append(np)


    return ans

print(floodfill())
for i in range(q):
    a,b = [int(i) for i in input().split()]
    rows[a-1][b-1] = '#'
    print(floodfill())