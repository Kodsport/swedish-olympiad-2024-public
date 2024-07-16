#!/usr/bin/python3

l,r = map(int,input().split())

Q = int(input())

cameras = {}

for _ in range(Q):

    inp = input().split()

    if inp[0] == "+":
        id,a,b = map(int,inp[1:])

        cameras[id] = (a,b)
    else:
        id = int(inp[1])
        if id in cameras:
            del cameras[id]

    

    bestStart = -1
    bestEnd = 10**9+2

    for id in cameras:
        a,b=cameras[id]
        if a<=l:
            bestStart = max(b,bestStart)
        elif b>=r:
            bestEnd = min(bestEnd,a)
    
    if bestStart>=r or -1<bestEnd<l:
        print(1)
    elif -1<bestEnd<=bestStart:
        print(2)
    else:
        print(-1)

