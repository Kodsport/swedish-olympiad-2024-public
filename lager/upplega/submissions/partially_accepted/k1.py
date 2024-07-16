#!/usr/bin/env python3

#testa att endast välja de K träd som ger mest snö

n,k = map(int,input().split())

trees = [*map(int,input().split())]
sizes = [*map(int,input().split())]

snow = [0 for _ in range(n)]
for tree in range(n):
    heights = [*map(int,input().split())]
    lengths = [*map(int,input().split())]
    for i in range(len(heights)):

        snow[tree] += abs(lengths[i])

snow.sort(reverse=1)

print(sum(snow[:k]))
    

