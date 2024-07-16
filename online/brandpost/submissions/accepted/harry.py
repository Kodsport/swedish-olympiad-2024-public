#!/usr/bin/python3

#O(NH + WH)
#Solution idea by Erik Hedin
#Implemented by Harry Zhang


w,h,n = map(int,input().split())
waterLevel = [[0]*w for _ in range(h)]
delta = [[0]*w for _ in range(h)]


hydrants = []
for _ in range(n):
    x,y = map(int,input().split())
    x -= 1
    y -= 1
    hydrants.append((x,y))



#Start (0,0) ---> Goal (w-1,h-1)

INF = 10**18

BFS = [(0,0)]
depth = [[-1]*w for _ in range(h)]
setWater = [[INF]*w for _ in range(h)]

depth[0][0] = 0
setWater[0][0] = 0


def currWaterLevel(x,y):
    currTime = x+y
    
    water = 0
    for hx,hy in hydrants:
        water += max(0,currTime-(abs(x-hx)+abs(y-hy))+1)
    return water


#Initierar värden för alla (0,y)
for i in range(h):
    waterLevel[i][0] = currWaterLevel(0,i) #O(n)


for r in range(h): #O(h)
    for x,y in hydrants: #O(n)
        if x+r < abs(r-y):
            continue
        temp = x-r + abs(r-y)

        if max(0,(temp+1)//2)<w:
            delta[r][max(0,(temp+1)//2)]+=1
        
        if max(0,(temp//2)+1)<w:
            delta[r][max(0,(temp//2)+1)]+=1
        
        if x+1<w:
            delta[r][x+1]-=2


    currDelta = delta[r][0]
    for c in range(1,w):
        currDelta+=delta[r][c]
        waterLevel[r][c] = waterLevel[r][c-1]+currDelta

for x,y in BFS:

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
