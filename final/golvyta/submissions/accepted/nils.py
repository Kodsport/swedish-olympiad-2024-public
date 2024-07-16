#!/usr/bin/python3

def solve(d, goal):
    lo = 0
    hi = len(d)+2
    while lo < hi-1:
        mid = (lo+hi)//2
        x = 0
        for dx in d:
            x += dx
            x = max(0, x)
            x = min(mid-1,x)
        if x >= goal:
            hi = mid
        else:
            lo = mid
    if lo == len(d)+1:
        return -1
    return hi

input()
s = input()
r,c = map(int,input().split())
d1 = []
d2 = []
for ch in s:
    if ch == '<':
        d2.append(-1)
    if ch == '>':
        d2.append(1)
    if ch == '^':
        d1.append(-1)
    if ch == 'v':
        d1.append(1)

n = solve(d1, r)
m = solve(d2, c)

if n == -1 or m == -1:
    print(-1)
else:
    print(n*m)
