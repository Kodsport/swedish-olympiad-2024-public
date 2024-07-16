#!/usr/bin/env python3
import sys
sys.setrecursionlimit(2*10**5)
n,k = map(int,input().split())

trees = [*map(int,input().split())]
sizes = [*map(int,input().split())]

#branches = [[] for _ in range(n)]
#branches = [[[*map(int,input().split())],[*map(int,input().split())]] for _ in range(n)]
gaps = [[] for _ in range(n+1)]
for tree in range(n):
    heights = [*map(int,input().split())]
    lengths = [*map(int,input().split())]
    for i in range(len(heights)):
        #branches[tree].append((heights[i],lengths[i]))
        if lengths[i]<0:
            gaps[tree].append((heights[i],lengths[i]))
        else:
            gaps[tree+1].append((heights[i],lengths[i]))
    
leftDrop    = [0]*(n+1) #Amount of snow dropped in the i:th gap if the left tree gets shaken
rightDrop   = [0]*(n+1) #Amount of snow dropped in the i:th gap if the right tree gets shaken
totalDrop   = [0]*(n+1) #Amount of snow dropped in the i:th gap if the both trees gets shaken

for i in range(n+1):
    treeLeft = i-1
    treeRight = i
    if treeLeft == -1:
        dist = trees[i]
    elif treeRight == n:
        dist = 10**9
    else:
        dist = trees[treeRight]-trees[treeLeft]-1
    
    total = left = right = 0
    blockedLeft = 0
    blockedRight = 0 #Length blocked for tree to the right

    gaps[i].sort()
    for h,l in gaps[i]:
        total += abs(l)
        if l<0:
            right += min(-l,dist-blockedRight)
            blockedLeft = max(blockedLeft,-l)
        else:
            left += min(l,dist-blockedLeft)
            blockedRight = max(blockedRight,l)
    leftDrop[i] = left
    rightDrop[i] = right
    totalDrop[i] = total

totalDropPrefix = [0]
for x in totalDrop:
    totalDropPrefix.append(totalDropPrefix[-1] + x)

def debugDrops():
    print(leftDrop)
    print(rightDrop)
    print(totalDrop)

#Min snow to drop from the index tree, with moves trees left to push.
memo = [[[-1,-1] for _ in range(k+1)] for _  in range(n+1)]
def dp(index, moves, pushedLast = 0):
    assert(moves<=n-index), "There are more moves than pushes left to use"
    
    if index == n:
        return 0
    if moves == 0:
        return 0
    
    if memo[index][moves][pushedLast] != -1:
        return memo[index][moves][pushedLast]
    temp = 0

    
    if n-index == moves:
        #Always push
        
        if pushedLast:
            temp -= leftDrop[index]
            return temp + totalDropPrefix[-1] - totalDropPrefix[index] #Small optimisation
        else:
            return totalDropPrefix[-1] - totalDropPrefix[index+1] + rightDrop[index]
    
        #Alternatively 
        #return dp(index+1, moves-1, 1) - pushedLast*leftDrop[index] + pushedLast*totalDrop[index] + (1-pushedLast)*rightDrop[index] + leftDrop[index+1] 
    
    
    push = dp(index+1, moves-1, 1) - pushedLast*leftDrop[index] + pushedLast*totalDrop[index] + (1-pushedLast)*rightDrop[index] + leftDrop[index+1] 
    dont = dp(index+1, moves, 0)
    memo[index][moves][pushedLast] = min(push, dont)
    return min(push, dont)

print(dp(0,k,0))
debugDrops()
