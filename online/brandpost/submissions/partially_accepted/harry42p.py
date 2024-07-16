#!/usr/bin/python3

#O(WHN)

w,h,n = map(int,input().split())


hydrants = []
for _ in range(n):
    x,y = map(int,input().split())
    x -= 1
    y -= 1
    hydrants.append((x,y))


#Start (0,0) ---> Goal (w-1,h-1)

BFS = [(0,0)]
depth = [[-1]*w for _ in range(h)]
setWater = [[10**9]*w for _ in range(h)]

depth[0][0] = 0
setWater[0][0] = 0


currTime=0

def currWaterLevel(x,y):
    currTime=x+y
    
    water=0
    for hx,hy in hydrants:
        water+=max(0,currTime-(abs(x-hx)+abs(y-hy))+1)

    return water

for x,y in BFS:

    setWater[y][x] += currWaterLevel(x,y)

    for dx,dy in [(1,0),(0,1)]: #We can only move up or to the right
        if x+dx>=w or y+dy>=h:
            continue

        setWater[y+dy][x+dx] = min(setWater[y+dy][x+dx],setWater[y][x])    

        if depth[y+dy][x+dx] != -1:
            continue

        depth[y+dy][x+dx] = depth[y][x]+1
        
        BFS.append((x+dx,y+dy))

print(setWater[h-1][w-1])
