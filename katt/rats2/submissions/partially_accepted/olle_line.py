#!/usr/bin/python3

n, k = [int(i) for i in input().split()]

rats = [int(i)-1 for i in input().split()]
targets = [int(i)-1 for i in input().split()]

for i in range(n):
    print(1, 1)
    rats = [int(i)-1 for i in input().split()]

for i in range(k-1,-1,-1):
    while rats[i] != targets[i]:
        print(n-rats[i], *[i+1 for i in range(rats[i], n)])
        rats = [int(i)-1 for i in input().split()]
        
print("activate!")