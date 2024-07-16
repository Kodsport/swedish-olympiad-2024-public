#!/usr/bin/python3

n,t,s = map(int,input().split())

if n == 0:
    print(s)
    exit()

assert n == 1

l,r = map(int,input().split())
print(s-(r-l))
