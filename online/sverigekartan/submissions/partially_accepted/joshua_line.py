#!/usr/bin/env python3
r=int(input())
c=int(input())
q=int(input())
row = input()

spos = -1
for i in range(c):
    if row[i]=='S':
        spos = i

ans = 0
i=spos+1
while i < c and row[i]=='#':
    ans+=1
    i+=1

i=spos-1
while i >= 0 and row[i]=='#':
    ans+=1
    i-=1

print(ans+1)