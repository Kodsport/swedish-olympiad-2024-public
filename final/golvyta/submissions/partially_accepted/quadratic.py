#!/usr/bin/python3

def solve(d, goal):
    n = goal+1
    for n in range(goal+1, len(d)+2):
        x = 0
        bumps = 0
        for dx in d:
            x += dx
            x = max(0, x)
            if x == n:
                bumps += 1
            x = min(n-1,x)
        if x == goal:
            return n
        if bumps == 0:
            break
    return -1

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
