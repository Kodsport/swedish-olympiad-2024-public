#!/usr/bin/python3

n, m = [int(i) for i in input().split()]

names = input().split()
hunters = [names[0]]

ans = []
for i in range(m):
    name1, _, name2 = input().split()
    if name1 not in hunters:
        if name1 not in ans:
            ans.append(name1)
    
    if name1 in hunters:
        hunters.remove(name1)
    
    if name2 not in hunters:
        hunters.append(name2)

print(len(ans))
print(*sorted(ans))
