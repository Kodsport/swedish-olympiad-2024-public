#!/usr/bin/env python3

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

for i in range(n+1): #Calculate for the amount of snow between each pair of adjacent trees
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
            assert dist>=blockedRight, f"{dist}, {blockedRight}"
            blockedLeft = max(blockedLeft,-l)
        else:
            left += min(l,dist-blockedLeft)
            assert dist>=blockedLeft, f"{dist}, {blockedLeft}"
            blockedRight = max(blockedRight,l)
    leftDrop[i] = left
    rightDrop[i] = right
    totalDrop[i] = total
    

def dp(index, pushedLast = 1):
    for i in range(n-1,-1,-1):
        for push in range(2):
            save,saveK = memo[i+1][0]
            save += push*(totalDrop[i]-leftDrop[i]) + (1-push)*rightDrop[i] + totalDrop[i+1]-rightDrop[i+1] - mid
            saveK += 1
            
            dont,dontK = memo[i+1][1]
            if save > dont:
                best = save
                bestK = saveK
            else:
                best = dont
                bestK = dontK
            memo[i][push] = (best,bestK)
    
    return memo[0][1]

memo = [[(0,0),(0,0)] for _  in range(n+1)]
lo = 0
hi = 10**9
for i in range(50):
    mid = (lo+hi)/2
    ans,ansK = dp(0,1)

    if ansK == k:
        lo = hi = mid
        break
    elif ansK > k: 
        lo = mid
    else:
        hi = mid

mid = hi
print(round(dp(0,1)[0] + mid*k))
