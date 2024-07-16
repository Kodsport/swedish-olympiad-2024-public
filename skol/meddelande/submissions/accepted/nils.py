#!/usr/bin/env python3
n,m = map(int,input().split())
ans = ""
for _ in range(n):
    ans += input().replace('.','')
print(ans)
