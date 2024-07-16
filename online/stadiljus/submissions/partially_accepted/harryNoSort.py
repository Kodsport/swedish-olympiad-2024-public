#!/usr/bin/python3

n = int(input())
pris = int(input())
maxAverage = int(input())
L = [*map(int,input().split())]

output = temp = 0
for length in L:
    if pris*length + temp > maxAverage * (output + 1):
        print(output)
        exit()
    
    temp += pris*length
    output += 1

print(output)
