#!/usr/bin/env python3
r=int(input())
c=int(input())
q=int(input())
row = [i for i in input()]

spos = -1
for i in range(c):
    if row[i]=='S':
        spos = i

def calculate():
    ans = 0
    i=spos+1
    while i < c and row[i]=='#':
        ans+=1
        i+=1

    i=spos-1
    while i >= 0 and row[i]=='#':
        ans+=1
        i-=1
    return ans+1

print(calculate())
for i in range(q):
    a,b = [int(i) for i in input().split()]
    row[b-1] = '#'
    print(calculate())