#!/usr/bin/python3

n, m = [int(i) for i in input().split()]

a, b = input().split()

tagger = a

ans = set()

for i in range(m):
    x, _, y = input().split()
    if x != tagger:
        ans.add(x)
    else:
        tagger = y

print(len(ans))
print(*sorted(list(ans)))