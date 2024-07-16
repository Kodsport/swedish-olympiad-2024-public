#!/usr/bin/env python3

import sys
from collections import defaultdict
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
T = [input() for _ in range(m)]
T = [list(i) for i in set(T)]
T.sort(reverse=True, key = lambda i: len(i))

#### Precalculations start

rhashes = [hash_string(t) for t in T]
string_hashes = set(hashes[-1] for hashes in rhashes)

prefix_hashes = defaultdict()
for j,hashes in enumerate(rhashes):
    thash = hashes[-1] 
    string_hashes.add(thash)
    
    # If thash is not a prefix of an earlier string
    if thash not in prefix_hashes:
        for h in hashes:
            prefix_hashes[h] = j

# For each string in T, store which lengths of prefixes are in T
valid_prefix = []
for hashes in rhashes:
    tmp = [i for i in range(len(hashes)) if hashes[i] in string_hashes]
    valid_prefix.append(tmp)

#### Precalculations Done

n = len(S)
Shashes = hash_string(S)

def substring_hash(l, r):
    return (Shashes[r] - Shashes[l]) * b_inv_power[l] % MOD


found = [BIG] * (n + 1)
found[0] = 0

for i in range(n):
    if found[i] == BIG:
        continue
    
    # Find string in T with longest LCP
    l = i
    r = n
    while l < r:
        mid = (l + r + 1) // 2
        if substring_hash(i, mid) in prefix_hashes:
            l = mid
        else:
            r = mid - 1
    
    LCP_length = r - i

    if LCP_length == 0:
        # No string in T starts with S[i]
        continue

    possible_matches = valid_prefix[prefix_hashes[substring_hash(i, i + LCP_length)]]
    
    for d in possible_matches:
        if d <= LCP_length:
            found[i + d] = min(found[i + d], found[i] + 1)

if found[-1] == BIG:
    print(-1)
else:
    print(found[-1])