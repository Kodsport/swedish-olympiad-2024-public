#!/usr/bin/env python3

s = input()
mapping = {}
for i in s:
    if not i in mapping:
        mapping[i]=len(mapping)

n=len(mapping)
cost=[[0 for i in range(n)] for j in range(n)]

for i in range(len(s)-1):
    a=mapping[s[i]]
    b=mapping[s[i+1]]
    cost[a][b]+=1
    cost[b][a]+=1

dp = [100000 for i in range(pow(2,n))]
dp[0]=0
for mask in range(pow(2,n)):
    v = dp[mask]
    for i in range(n):
        if mask&(1<<i):
            continue
        for j in range(n):
            if not (mask&(1<<j)):
                continue
            v+=cost[i][j]
    for i in range(n):
        if mask&(1<<i):
            continue
        dp[mask|(1<<i)] = min(dp[mask|(1<<i)], v)

print(dp[-1])
