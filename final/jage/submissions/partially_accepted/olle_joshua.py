#!/usr/bin/python3

n, m = [int(i) for i in input().split()]

names = input().split()


joshua = "joshua"
joshua_hunter = (names[0] == joshua)
joshua_cheated = False

for i in range(m):
    name1, _, name2 = input().split()
    
    if name1 == joshua and not joshua_hunter:
        joshua_cheated = True
    
    if name1 == joshua:
        joshua_hunter = False
    
    if name2 == joshua:
        joshua_hunter = True

ans = [joshua] if joshua_cheated else []

print(len(ans))
print(*sorted(list(ans)))
