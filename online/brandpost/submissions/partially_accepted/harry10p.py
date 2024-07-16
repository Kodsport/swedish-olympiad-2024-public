#!/usr/bin/python3

#This solution is not correct, since it's assuming we should always go by the edges
#10p.

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

BFS = [(0,0,"up"),(0,0,"right")]
depth = [[-1]*w for _ in range(h)]
setWater = [[10**9]*w for _ in range(h)]

setWater[0][0] = 0
depth[0][0] = 0

currTime=0

def simulateOneMinute(currTime):
    currTime+=1
    for x in range(w):
        for y in range(h):
            for i,j in hydrants:
                if abs(i-x)+abs(y-j)<=currTime:
                    waterLevel[y][x]+=1
    return currTime

for x,y,dir in BFS:

    while currTime < depth[y][x]: #runs maximum (W+H) times
        currTime = simulateOneMinute(currTime) #O(W*H*N)
    
    setWater[y][x] += waterLevel[y][x]
    if (x,y,dir)==(0,0,"right"):
        setWater[y][x] -= waterLevel[y][x]
    
    if dir=="up":
        dx,dy=0,1
        if x+dx>=w or y+dy>=h:
            dx,dy=dy,dx
            dir="right"
        if x+dx>=w or y+dy>=h:
            continue

        setWater[y+dy][x+dx] = min(setWater[y+dy][x+dx],setWater[y][x])    

        if depth[y+dy][x+dx] != -1:
            continue

        depth[y+dy][x+dx] = depth[y][x]+1
        
        BFS.append((x+dx,y+dy,dir))
    else:
        dx,dy=1,0
        if x+dx>=w or y+dy>=h:
            dx,dy=dy,dx
            dir="up"
        if x+dx>=w or y+dy>=h:
            continue

        setWater[y+dy][x+dx] = min(setWater[y+dy][x+dx],setWater[y][x])    

        if depth[y+dy][x+dx] != -1:
            continue

        depth[y+dy][x+dx] = depth[y][x]+1
        
        BFS.append((x+dx,y+dy,dir))
        
print(setWater[h-1][w-1])
