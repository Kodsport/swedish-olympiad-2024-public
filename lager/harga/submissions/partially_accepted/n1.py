#!/usr/bin/python3

n,m = map(int,input().split())

X = list(map(int,input().split()))
F = list(map(int,input().split()))
for i in range(n):
    X[i] -= 1
for i in range(m):
    F[i] -= 1

seen = [0] * m
i = X[0]
while seen[i] == 0:
    seen[i] = 1
    i = F[i]

if sum(seen) == m:
    ms = [m] * n
    print(*ms)
else:
    print(-1)