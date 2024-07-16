#!/usr/bin/python3
import bisect
n,t,s = map(int,input().split())

if n == 0:
    print(s)
    exit()

reklam = []
lens = []
for _ in range(n):
    l,r = map(int,input().split())
    reklam.append(l)
    reklam.append(r)
    lens.append(r-l)

prefix = [0]
for x in lens:
    prefix.append(x + prefix[-1])

if s == t:
    print(t - sum((-1)**(i%2==0)*reklam[i] for i in range(2*n)))
    exit()
        
best = t*2

#Idea:
#For each index in reklam, binary search the other end.

for i in range(2*n):
    ind = bisect.bisect_right(reklam,reklam[i]+s)

    ads = - prefix[-(-i//2)]

    if ind == 2*n:
        ads += prefix[-1]
    else:
        ads += prefix[-(-(ind-1)//2)]
        if ind%2:
            ads += reklam[i]+s-reklam[ind-1]

    best = min(best,s-ads)

print(best)


