#!/usr/bin/env python3
import sys
from collections import defaultdict
import bisect
input = lambda: sys.stdin.buffer.readline().rstrip()

b = 214234
MOD = 2**61 - 1
b_inv = pow(b, MOD - 2, MOD)
BIG = 10**5 + 100

b_power = [1]
for _ in range(BIG):
    b_power.append(b * b_power[-1] % MOD)
b_inv_power = [1]
for _ in range(BIG):
    b_inv_power.append(b_inv * b_inv_power[-1] % MOD)

def hash_string(S):
    hashes = [0]
    for bpow, c in zip(b_power,S):
        hashes.append((hashes[-1] + c * bpow) % MOD)
    return hashes

n = int(input())
S = list(input())

m = int(input())
T = [list(input()) for _ in range(m)]

lengths = set(len(t) for t in T)
Thashes = set(hash_string(t)[-1] for t in T)

Shashes = hash_string(S)
def substring_hash(l, r):
    return (Shashes[r] - Shashes[l]) * b_inv_power[l] % MOD

found = [BIG] * (n + 1)
found[0] = 0

for i in range(n):
    if found[i] == BIG:
        continue
    
    found_plus_1 = found[i] + 1
    for d in lengths:
        if i + d <= n and substring_hash(i, i + d) in Thashes:
            found[i + d] = min(found[i + d], found_plus_1)

if found[-1] == BIG:
    print(-1)
else:
    print(found[-1])