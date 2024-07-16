#!/usr/bin/env python3

n = int(input())
t = input()
m = int(input())
dict = []
for i in range(m):
    dict.append(input())

import random


base = random.randrange(130, int(1e9))

mod = 18446744073709551615 # 2^64-1

# Hand-unrolled mersenne prime code only for it to be slower than a snail
# Probably from frequent int64-> int128t conversions
class Hashing:
    def __init__(self, s):
        ha = [0 for i in range(len(s)+1)]
        pw = [0 for i in range(len(s)+1)]
        pw[0]=1
        for i in range(len(s)):
            p = ha[i]*base
            a = p&mod
            t = (a+(p>>64))&mod
            t += 1 if t < a else 0
            t = (t+s[i])&mod
            ha[i+1] = t+(1 if t < s[i] else 0)
            p = pw[i]*base
            a = p&mod
            t = (a+(p>>64))&mod
            pw[i+1] = t+(1 if t < a else 0)
        self.pw = pw
        self.ha = ha

    def hashinterval(self, a, b): # [a,b)
        p = self.ha[a]*self.pw[b - a]
        a = p&mod
        t = (a+(p>>64))&mod
        t += 1 if t < a else 0
        t = ~t
        t = (t+self.ha[b])&mod
        return t+(1 if t < self.ha[b] else 0)

words = []
groupmap = {}
for d in dict:
    h = Hashing(list(ord(c) for c in d)).hashinterval(0, len(d))
    if len(d) not in groupmap:
        groupmap[len(d)]=set()
    groupmap[len(d)].add(h)

for g in groupmap.items():
    words.append((g[1], g[0]))

hasher = Hashing(list(ord(c) for c in t))
dp = [10000000 for i in range(n+1)]
dp[0]=0
for i in range(n):
    for w in words:
        if i+w[1]>n:
            continue
        
        works = hasher.hashinterval(i,i+w[1]) in w[0]
        if works:
            dp[i+w[1]] = min(dp[i+w[1]], dp[i]+1)

print(dp[-1])