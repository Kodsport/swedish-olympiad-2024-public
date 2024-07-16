#!/usr/bin/python3

#O(N+(W+H)*WH)
#Solution idea by Erik Hedin
#Implemented by Harry Zhang


w,h,n = map(int,input().split())


rate=[[0]*w for _ in range(h)]
waterLevel=[[0]*w for _ in range(h)]
U=[[0]*w for _ in range(h)]
D=[[0]*w for _ in range(h)]
L=[[0]*w for _ in range(h)]
R=[[0]*w for _ in range(h)]

"""
rate        #Number of hydrants that reach this cell
waterLevel  #Current water level
U           #Number of watersources above this cell that reach the top of this cell
D           #Number of watersources under this cell that reach the bottom of this cell
L           #Number of watersources to the left that reach the left wall of this cell
R           #Number of watersources to the right that reach the right wall of this cell
"""

hydrants = []
for _ in range(n):
    x,y = map(int,input().split())
    x -= 1
    y -= 1
    hydrants.append((x,y))
    rate[y][x]=1
    waterLevel[y][x]=1

    if 0<=x-1<w and 0<=y<h:
        R[y][x-1] += 1
    if 0<=x+1<w and 0<=y<h:
        L[y][x+1] += 1

    if 0<=x<w and 0<=y-1<h:
        U[y-1][x] += 1
    if 0<=x<w and 0<=y+1<h:
        D[y+1][x] += 1
    

def simulateOneMinute(currTime, rate,waterLevel,U,D,L,R):
    currTime+=1

    U2=[[0]*w for _ in range(h)]
    D2=[[0]*w for _ in range(h)]
    L2=[[0]*w for _ in range(h)]
    R2=[[0]*w for _ in range(h)]
    
    def up(x,y,V):
        
        if 0<=x-1<w and 0<=y<h:
            R2[y][x-1] += V

        if 0<=x+1<w and 0<=y<h:
            L2[y][x+1] += V

        if 0<=x<w and 0<=y-1<h:
            U2[y-1][x] += V

    def down(x,y,V):
        if 0<=x-1<w and 0<=y<h:
            R2[y][x-1] += V

        if 0<=x+1<w and 0<=y<h:
            L2[y][x+1] += V

        if 0<=x<w and 0<=y+1<h:
            D2[y+1][x] += V
    
    def right(x,y,V):
        if 0<=x-1<w and 0<=y<h:
            R2[y][x-1] += V
    
    def left(x,y,V):
        if 0<=x+1<w and 0<=y<h:
            L2[y][x+1] += V

    for y in range(h):
        for x in range(w):
                
            if R[y][x]:
                rate[y][x] += R[y][x]
                right(x,y,R[y][x])

            if L[y][x]:
                rate[y][x] += L[y][x]
                left(x,y,L[y][x])

            if U[y][x]:
                rate[y][x] += U[y][x]
                up(x,y,U[y][x])
            
            if D[y][x]:
                rate[y][x] += D[y][x]
                down(x,y,D[y][x])


    for y in range(h):
        for x in range(w):
            waterLevel[y][x]+= rate[y][x]

    U,U2=U2,U
    D,D2=D2,D
    L,L2=L2,L
    R,R2=R2,R
    
    return currTime, rate, waterLevel, U, D, L, R


#Start (0,0) ---> Goal (w-1,h-1)

INF = 10**9

BFS = [(0,0)]
depth = [[-1]*w for _ in range(h)]
setWater = [[INF]*w for _ in range(h)]

depth[0][0] = 0
setWater[0][0] = 0


currTime=0

for x,y in BFS:

    while currTime < depth[y][x]: #runs (W+H) times
        currTime, rate,waterLevel,U,D,L,R = simulateOneMinute(currTime, rate, waterLevel, U, D, L, R) #O(W*H)

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
