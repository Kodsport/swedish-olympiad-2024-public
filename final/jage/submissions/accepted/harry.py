#!/usr/bin/python3

n,m = map(int,input().split())

names = input().split()

active = {name:0 for name in names}

cheated = {name:0 for name in names}

active[names[0]] = 1

for _ in range(m):
    a,b,c = input().split()
    if not active[a]:
        cheated[a] = 1
    active[a] = 0
    active[c] = 1

out = []

for name in cheated:
    if cheated[name]:
        out.append(name)

print(len(out))
print(*sorted(out))
