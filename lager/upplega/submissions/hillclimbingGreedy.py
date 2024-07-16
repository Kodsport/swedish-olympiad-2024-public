#!/usr/bin/env python3
import heapq
import random
import time
startTime = time.time()

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


def checkSnow(i):
    if used[i]:
        return 0
    temp = 0
    if i != 0:
        if used[i-1]:
            temp += rightDrop[i]
        else:
            temp += totalDrop[i] - leftDrop[i]
    else:
        temp += rightDrop[i]
    
    if i != n-1:
        if used[i+1]:
            temp += leftDrop[i+1]
        else:
            temp += totalDrop[i+1]-rightDrop[i+1]
    else:
        temp += leftDrop[i+1]
    
    return temp

queue = []
used = [0]*n
picked = 0
out = 0

for i in range(n):
    assert checkSnow(i) == (totalDrop[i]-leftDrop[i]) + (totalDrop[i+1]-rightDrop[i+1])
    heapq.heappush(queue, (-checkSnow(i),i))

while picked<k:
    snow,i = heapq.heappop(queue)
    if checkSnow(i) == -snow:
        out += -snow
        used[i] = 1
        picked += 1
    else:
        heapq.heappush(queue, (-checkSnow(i),i))


savedOut = out

if n == k:
    print(savedOut)
    exit()

orig = used[:]
choices = [*range(n)]


used = orig[:]
tempOut = savedOut 

while time.time() - startTime < 2.9:

    a,b = random.sample(choices,2)

    if used[a] == used[b]:
        continue

    if used[b]:
        a,b=b,a


    used[a] = 0
    tempOut -= checkSnow(a)

    if checkSnow(a) > checkSnow(b):
        tempOut = tempOut + checkSnow(a)
        used[a] = 1
    else:
        tempOut = tempOut + checkSnow(b)
        used[b] = 1



print(tempOut)

