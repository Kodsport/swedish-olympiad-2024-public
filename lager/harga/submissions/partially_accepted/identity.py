#!/usr/bin/python3

n,m = map(int,input().split())

X = list(map(int,input().split()))
F = list(map(int,input().split()))
for i in range(n):
    X[i] -= 1

next = [-1] * (2*n)
largest = [-1] * m

for i in range(n):
    X.append(X[i])

for i in range(2*n)[::-1]:
    next[i] = largest[X[i]]
    largest[X[i]] = i

if min(largest) == -1:
    print(-1)
else:
    ANS = []
    ans = max(largest)
    for i in range(n):
        ANS.append(ans-i+1)
        ans = max(ans, next[i])
    print(*ANS)

