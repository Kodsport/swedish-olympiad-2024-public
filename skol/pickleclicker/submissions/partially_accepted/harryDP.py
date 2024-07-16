#!/usr/bin/env python3
import sys
sys.setrecursionlimit(10**5)

#Den här koden är O(n*t^2)
#Funkar bäst med stora p_i värden, och låga t värden.

n,goal = [int(i) for i in input().split()]

p = []
c = []

for _ in range(n):
    x,y=map(int,input().split())
    p.append(x)
    c.append(y)


memo = {}

def dp(pickles, factorySpeed):
    if (pickles, factorySpeed) in memo:
        return memo[(pickles, factorySpeed)]
    
    temp = pickles
    pickles+=factorySpeed
    
    if pickles >= goal:
        return 1
    
    best = dp(pickles, factorySpeed)

    for i in range(n):
        if pickles>=c[i]:
            best=min(best,dp(pickles-c[i], factorySpeed+p[i]))

    memo[(temp, factorySpeed)] = best+1
    return best+1

print(dp(0,p[0]))
