#!/usr/bin/python3

def check(n,m):
    x,y = 0,0
    for ch in s:
        dx,dy = M[ch]
        x += dx
        y += dy
        x = max(0,x)
        x = min(n-1,x)
        y = max(0,y)
        y = min(m-1,y)
    return (x == r and y == c)

M = {'>': (0,1), '<': (0,-1), 'v': (1,0), '^': (-1,0)}

input() # length
s = input()
r,c = map(int,input().split())

ans = 10**9
assert(len(s) <= 400)
for n in range(r+1, len(s)+1):
    for m in range(c+1, len(s)+1):
        if check(n,m) and n*m < ans:
            ans = n*m
            break
    if ans != 10**9:
        break

if ans == 10**9:
    ans = -1
print(ans)
