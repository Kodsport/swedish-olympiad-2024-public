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

memo = [-1 for i in range(2**15)]
def dp(cur_pos, mask):
    if cur_pos==n:
        return 0
    
    if memo[mask]!=-1:
        return memo[mask]
    
    ret = 10000000000000
    for i in range(n):
        if mask&(1<<i):
            continue
        ret=min(ret,dp(cur_pos+1,mask|(1<<i)))
    c=0

    for i in range(n):
        if mask&(1<<i):
            continue
        for j in range(n):
            if not (mask&(1<<j)):
                continue
            c+=cost[i][j]

    ret+=c
    memo[mask]=ret
    return ret


print(dp(0,0))