#!/usr/bin/python3

#O(WHN(W+H))

w,h,n = map(int,input().split())

waterLevel = [[0]*w for _ in range(h)]


hydrants = []
for _ in range(n):
    x,y = map(int,input().split())
    x -= 1
    y -= 1
    hydrants.append((x,y))
    waterLevel[y][x] = 1


#Start (0,0) ---> Goal (w-1,h-1)

BFS = [(0,0)]
depth = [[-1]*w for _ in range(h)]
setWater = [[10**9]*w for _ in range(h)]

depth[0][0] = 0
setWater[0][0] = 0


currTime=0

def simulateOneMinute(currTime):
    currTime+=1
    for x in range(w):
        for y in range(h):
            for i,j in hydrants:
                if abs(i-x)+abs(y-j)<=currTime:
                    waterLevel[y][x]+=1
    return currTime

for x,y in BFS:

    while currTime < depth[y][x]: #runs maximum (W+H) times
        currTime = simulateOneMinute(currTime) #O(W*H*N)
    
    setWater[y][x] += waterLevel[y][x]

    for dx,dy in [(1,0),(0,1)]: #We can only move up or to the right
        if x+dx>=w or y+dy>=h:
            continue

        setWater[y+dy][x+dx] = min(setWater[y+dy][x+dx],setWater[y][x])    

        if depth[y+dy][x+dx] != -1:
            continue

        depth[y+dy][x+dx] = depth[y][x]+1
        
        BFS.append((x+dx,y+dy))
    
print(setWater[h-1][w-1])
