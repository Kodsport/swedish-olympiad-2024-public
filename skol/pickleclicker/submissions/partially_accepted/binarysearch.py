#!/usr/bin/env python3

n,t = [int(i) for i in input().split()]
buildings = [[int(i) for i in input().split()] for j in range(n)]

lo = 0
hi = int(1e5+1)

def possible(goal):
    moneys = 0
    builds = [0 for i in range(n)]
    builds[0]=1
    daysleft=goal
    for i in range(goal):
        for j in range(n):
            moneys += builds[j]*buildings[j][0]
        daysleft-=1
        
        best = 0
        bestv = -1

        for j in range(n):
            profit = buildings[j][0]*daysleft-buildings[j][1]
            if profit>best and moneys>=buildings[j][1]:
                best=profit
                bestv=j

        if bestv!=-1:
            moneys -= buildings[bestv][1]
            builds[bestv]+=1
    if moneys>=t:
        return True
    return False


while hi-lo>1:
    mid = (lo+hi)//2
    if possible(mid):
        hi = mid
    else:
        lo=mid

print(hi)