#!/usr/bin/python3
#@EXPECTED_GRADES@ AC TLE WA WA TLE

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
                best=2
                break #This is wrong. If i find an answer with best=2, there could still be an answer w best=1

        if best==1 or best==2:
            break
    print(best)


