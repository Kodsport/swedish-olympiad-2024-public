#!/usr/bin/env python3

n,t = [int(i) for i in input().split()]

p = []
c = []

for _ in range(n):
    x,y=map(int,input().split())
    p.append(x)
    c.append(y)


l=0
r=t
def simulate(time):
    pickles=0
    speed=p[0]

    for currTime in range(time+1):
        pickles+=speed
        
        options=[]
        for store in range(n):
            if pickles>=c[store]:
                options.append((p[store]*(time-currTime)-c[store],store))
        
        options.sort(reverse=1)

        if options:
            if options[0][0]>0:
                pickles-=c[options[0][1]]
                speed+=p[options[0][1]]
    

    if pickles>=t:
        return 1
    else:
        return 0


while l<r:
    mid=(l+r)//2

    if simulate(mid):
        r=mid
    else:
        l=mid+1

print(l+1) #+1 eftersom jag räknar med att antalet pickles ökas redan på sekund 0.
