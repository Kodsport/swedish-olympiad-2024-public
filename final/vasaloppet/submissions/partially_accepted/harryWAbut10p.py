#!/usr/bin/python3

n,t,s = map(int,input().split())

if n == 0:
    print(s)
    exit()

reklam = []
for _ in range(n):
    l,r = map(int,input().split())
    reklam.append(l)
    reklam.append(r)
reklam.append(t)

if s == t:
    print(t - sum((-1)**(i%2==0)*reklam[i] for i in range(2*n)))
    exit()
        
best = t*2

prev = lind = rind = ads = buffer = 0

while rind < 2*n:
    if reklam[rind+1] >= s:
        break

    rind += 1
    if rind%2: #om rind är udda
        ads += reklam[rind]-reklam[rind-1]

if rind%2 == 0 and rind != 2*n:

    ads += s-reklam[rind]
    buffer = s-reklam[rind]

best = min(best,s-ads) #testar att gå och åka skidor direkt

while lind < 2*n: #flyttar lind ett steg
    while rind < 2*n: #flyttar rind så långt som det går
        if reklam[rind+1] >= s + reklam[lind]:
            break

        if buffer:
            ads -= buffer
            buffer = 0
        rind += 1
        if rind%2: #om rind är udda
            ads += reklam[rind]-reklam[rind-1]
    if buffer:
        ads -= buffer
        buffer = 0
    if rind%2 == 0 and rind != 2*n:
        ads += (s + reklam[lind])-reklam[rind]
        buffer = (s + reklam[lind])-reklam[rind]

    best = min(best,s-ads)
    
    lind += 1
    if lind % 2:
        ads -= reklam[lind]-reklam[lind-1]+1

best = min(best,s-ads)

print(best)
