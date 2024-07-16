#!/usr/bin/python3
s = input()
k = int(input())
n = len(s)
ans = n

for letter in s:
    temp = 0
    prev_skip = -10**9
    for i in range(n):
        if i-prev_skip+1 <= k:
            continue
        if s[i] != letter:
            temp += 1
            prev_skip = i
    ans = min(ans, temp)

print(ans)
