#!/usr/bin/python3

n, m = [int(i) for i in input().split()]

names = input().split()

a, _, b = input().split()
if a == names[0]:
    print(0)
    print()
else:
    print(1)
    print(a)
