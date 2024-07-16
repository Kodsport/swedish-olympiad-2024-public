#!/usr/bin/python3

n, m = [int(i) for i in input().split()]

names = input().split()
hunter = {name: False for name in names}
hunter[names[0]] = True

ans = set()
for i in range(m):
    name1, _, name2 = input().split()
    if not hunter[name1]:
        ans.add(name1)
    hunter[name1] = False
    hunter[name2] = True

print(len(ans))
print(*sorted(list(ans)))
