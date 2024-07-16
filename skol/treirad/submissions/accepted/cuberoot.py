#!/usr/bin/env python3

n = int(input())

i = 1
ans = 0
while i*(i+1)*(i+2)<n:
    ans+=1
    i+=1
print(ans)
