#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**5)

#Den här koden är O(t^n)
#Funkar bäst med stora p_i värden, och låga t värden.

n,goal = [int(i) for i in input().split()]

p = []
c = []

for _ in range(n):
    x,y=map(int,input().split())
    p.append(x)
    c.append(y)


memo = {}

def dp(pickles, bought):
    if (pickles, ".".join(map(str,bought))) in memo:
        return memo[(pickles, ".".join(map(str,bought)))]
    
    temp = pickles

    for i in range(n):
        pickles+=bought[i]*p[i]
    
    if pickles >= goal:
        return 1
    
    best = dp(pickles, bought)

    for i in range(n):
        if pickles>=c[i]:
            pickles-=c[i]
            bought[i]+=1
            best=min(best,dp(pickles, bought))
            bought[i]-=1
            pickles+=c[i]

    memo[(temp, ".".join(map(str,bought)))] = best+1
    return best+1

print(dp(0,[1]+[0]*(n-1)))
