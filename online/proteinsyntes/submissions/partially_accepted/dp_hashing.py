#!/usr/bin/env python3

n = int(input())
t = input()
m = int(input())
dict = []
for i in range(m):
    dict.append(input())

import random


# Credit: https://github.com/cheran-senthil/PyRival/blob/master/pyrival/strings/hashing.py
HMOD = int(1e9)+7
HBASE1 = random.randrange(130, HMOD)
HBASE2 = random.randrange(130, HMOD)


class Hashing:
    def __init__(self, s, mod=HMOD, base1=HBASE1, base2=HBASE2):
        self.mod, self.base1, self.base2 = mod, base1, base2
        self._len = _len = len(s)
        f_hash, f_pow = [0] * (_len + 1), [1] * (_len + 1)
        s_hash, s_pow = f_hash[:], f_pow[:]
        for i in range(_len):
            f_hash[i + 1] = (base1 * f_hash[i] + s[i]) % mod
            s_hash[i + 1] = (base2 * s_hash[i] + s[i]) % mod
            f_pow[i + 1] = base1 * f_pow[i] % mod
            s_pow[i + 1] = base2 * s_pow[i] % mod
        self.f_hash, self.f_pow = f_hash, f_pow
        self.s_hash, self.s_pow = s_hash, s_pow

    def hashed(self, start, stop):
        return (
            (self.f_hash[stop] - self.f_pow[stop - start] * self.f_hash[start]) % self.mod,
            (self.s_hash[stop] - self.s_pow[stop - start] * self.s_hash[start]) % self.mod,
        )

    def get_hashes(self, length):
        return (
            [(self.f_hash[i + length] - self.f_pow[length] * self.f_hash[i]) % self.mod for i in range(self._len - length + 1)],
            [(self.s_hash[i + length] - self.s_pow[length] * self.s_hash[i]) % self.mod for i in range(self._len - length + 1)],
        )

words = []
for d in dict:
    h = Hashing(list(ord(c) for c in d)).hashed(0, len(d))
    words.append((h, len(d)))

hasher = Hashing(list(ord(c) for c in t))
dp = [10000000 for i in range(n+1)]
dp[0]=0
for i in range(n):
    for w in words:
        if i+w[1]>n:
            continue
        
        works = hasher.hashed(i,i+w[1])==w[0]
        if works:
            dp[i+w[1]] = min(dp[i+w[1]], dp[i]+1)

print(dp[-1])