#!/usr/bin/env python3

n = int(input())
t = input()
m = int(input())
dict = []
for i in range(m):
    dict.append(input())

dp = [10000000 for i in range(n+1)]
dp[0]=0
for i in range(n):
    for w in dict:
        if i+len(w)>n:
            continue
        works = True
        for j in range(len(w)):
            if w[j]!=t[j+i]:
                works = False
                break

        if works:
            dp[i+len(w)] = min(dp[i+len(w)], dp[i]+1)

print(dp[-1])
