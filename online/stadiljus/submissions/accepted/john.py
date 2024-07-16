#!/usr/bin/env python3

n = int(input())
x = int(input())
y = int(input())
L = [int(i) for i in input().split()]
L.sort()

b = 0

antal = 0
for i in range(n):
    b += y
    b -= x*L[i]
    if b >= 0: antal += 1
    else: break

print(antal)