#!/usr/bin/python3

n,m = map(int,input().split())
#assert(n <= 1000 and m <= 1000)
X = list(map(int,input().split()))
F = list(map(int,input().split()))

unique = [1] * n
seen = [[0]*m for _ in range(n)]
ans = [-1] * n
for i in range(n):
    X[i] -= 1
    seen[i][X[i]] = 1

for i in range(m):
    F[i] -= 1

for t in range(1, n*m+2):
    x0 = X[0]
    for i in range(n):
        if ans[i] == -1 and unique[i] == m:
            ans[i] = t
        X[i] = F[X[(i+1)%n]]
        if i == n-1:
            X[i] = F[x0]
        if seen[i][X[i]] == 0:
            seen[i][X[i]] = 1
            unique[i] += 1
if min(ans) == -1:
    print(-1)
else:
    print(*ans)
