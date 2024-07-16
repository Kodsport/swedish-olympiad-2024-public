#!/usr/bin/python3

#O(N+(W+H)*WH)
#Solution idea by Erik Hedin
#Implemented by Harry Zhang

class cell:
    def __init__(self, x, y):
        self.rate = 0 #Number of hydrants that reach this cell
        self.waterLevel = 0 #Current water level
        self.U = 0 #Number of watersources above this cell that reach the top of this cell
        self.D = 0 #Number of watersources under this cell that reach the bottom of this cell
        self.L = 0 #Number of watersources to the left that reach the left wall of this cell
        self.R = 0 #Number of watersources to the right that reach the right wall of this cell


    def __str__(self):
        return f"{self.rate=} {self.waterLevel=} {self.U=} {self.D=} {self.L=} {self.R=}"
w,h,n = map(int,input().split())


cells=[[0]*w for _ in range(h)]
for y in range(h):
    for x in range(w):
        cells[y][x] = cell(x,y)

hydrants = []
for _ in range(n):
    x,y = map(int,input().split())
    x -= 1
    y -= 1
    hydrants.append((x,y))
    cells[y][x].rate=1
    cells[y][x].waterLevel=1

    if 0<=x-1<w and 0<=y<h:
        cells[y][x-1].R += 1
    if 0<=x+1<w and 0<=y<h:
        cells[y][x+1].L += 1

    if 0<=x<w and 0<=y-1<h:
        cells[y-1][x].U += 1
    if 0<=x<w and 0<=y+1<h:
        cells[y+1][x].D += 1
    

def simulateOneMinute(currTime, cells):
    currTime+=1
    cells2=[[None]*w for _ in range(h)]
    for y in range(h):
        for x in range(w):
            cells2[y][x] = cell(x,y)
            cells2[y][x].rate = cells[y][x].rate
            cells2[y][x].waterLevel = cells[y][x].waterLevel
    
    def up(x,y,V):
        if 0<=x-1<w and 0<=y<h:
            cells2[y][x-1].R += V

        if 0<=x+1<w and 0<=y<h:
            cells2[y][x+1].L += V

        if 0<=x<w and 0<=y-1<h:
            cells2[y-1][x].U += V

    def down(x,y,V):
        if 0<=x-1<w and 0<=y<h:
            cells2[y][x-1].R += V

        if 0<=x+1<w and 0<=y<h:
            cells2[y][x+1].L += V

        if 0<=x<w and 0<=y+1<h:
            cells2[y+1][x].D += V
    
    def right(x,y,V):
        if 0<=x-1<w and 0<=y<h:
            cells2[y][x-1].R += V
    
    def left(x,y,V):
        if 0<=x+1<w and 0<=y<h:
            cells2[y][x+1].L += V

    for y in range(h):
        for x in range(w):
            cells2[y][x].rate += cells[y][x].R
            right(x,y,cells[y][x].R)

            cells2[y][x].rate += cells[y][x].L
            left(x,y,cells[y][x].L)

            cells2[y][x].rate += cells[y][x].U
            up(x,y,cells[y][x].U)

            cells2[y][x].rate += cells[y][x].D
            down(x,y,cells[y][x].D)
    

    for y in range(h):
        for x in range(w):
            cells2[y][x].waterLevel += cells2[y][x].rate
    
    cells,cells2=cells2,cells

    return currTime,cells


#Start (0,0) ---> Goal (w-1,h-1)

BFS = [(0,0)]
depth = [[-1]*w for _ in range(h)]
setWater = [[10**9]*w for _ in range(h)]

depth[0][0] = 0
setWater[0][0] = 0

currTime=0

for x,y in BFS:

    while currTime < depth[y][x]: #runs (W+H) times
        currTime, cells = simulateOneMinute(currTime, cells) #O(W*H)

    setWater[y][x] += cells[y][x].waterLevel

    for dx,dy in [(1,0),(0,1)]: #We can only move up or to the right
        if x+dx>=w or y+dy>=h:
            continue

        setWater[y+dy][x+dx] = min(setWater[y+dy][x+dx],setWater[y][x])    

        if depth[y+dy][x+dx] != -1:
            continue

        depth[y+dy][x+dx] = depth[y][x]+1
        
        BFS.append((x+dx,y+dy))
    
print(setWater[h-1][w-1])
