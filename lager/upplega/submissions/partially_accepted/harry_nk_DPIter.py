#!/usr/bin/env python3
import sys

n,k = map(int,input().split())

trees = [*map(int,input().split())]
sizes = [*map(int,input().split())]

gaps = [[] for _ in range(n+1)]
for tree in range(n):
    heights = [*map(int,input().split())]
    lengths = [*map(int,input().split())]
    for i in range(len(heights)):

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



#Choose k trees where the snow never falls, returns how the max to save
memo = [[[0,0] for _ in range(k+1)] for _  in range(n+1)]
def dp(index, moves, pushedLast = 1):
    for i in range(n-1,-1,-1):
        for j in range(1,k+1):
            for push in range(2):
                temp = 0
                if n-i == j:
                    #Always save
                    if push:
                        temp = totalDrop[i] - leftDrop[i]
                    else:
                        temp = rightDrop[i]
                    memo[i][j][push] = temp + totalDropPrefix[-1] - totalDropPrefix[i+1]
                
                save = memo[i+1][j-1][0] + push*(totalDrop[i]-leftDrop[i]) + (1-push)*rightDrop[i] + totalDrop[i+1]-rightDrop[i+1] 
                dont = memo[i+1][j][1] 
                memo[i][j][push] = max(save,dont)

    return memo[0][k][1]

print(dp(0,k,1))

