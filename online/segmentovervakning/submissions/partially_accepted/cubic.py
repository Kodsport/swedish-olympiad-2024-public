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

    best=-1

    for id1 in cameras:
        for id2 in cameras:
            a,b=cameras[id1]
            c,d=cameras[id2]
            if a<=l<r<=b:
                best=1
                break
            elif min(a,c) <=l and max(b,d)>=r and (a<=c<=b<=d or c<=a<=d<=b):
                if best==-1:
                    best=2

        if best==1:
            break
    print(best)


