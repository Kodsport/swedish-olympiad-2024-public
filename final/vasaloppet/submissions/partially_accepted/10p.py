#!/usr/bin/python3

n,t,s = map(int,input().split())

l,r = map(int,input().split())
print(max(0,s-(r-l)))
