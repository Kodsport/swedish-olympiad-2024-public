#!/usr/bin/env python3

n = int(input())


ans = 0
for i in range(1,n):
    for j in range(n):
        if j*(j+1)*(j+2)==i:
            ans += 1
            break
print(ans)
