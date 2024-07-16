#!/usr/bin/python3

n, k = [int(i) for i in input().split()]

assert k == 1

def query(positions):
    positions = sorted(list(positions))
    print(len(positions), *[i+1 for i in positions])
    res = int(input())-1
    if res == target:
        print("activate!")
        exit(0)
    return res

root = rat = int(input())-1
target = int(input())-1

complete = [False]*n
parent = [-1]*n
children = [[] for i in range(n)]

def get_all_below(x):
    ret = [x]
    for c in children[x]:
        ret += get_all_below(c)
    return ret

def get_all_above(x):
    ret = []
    while parent[x] != -1:
        x = parent[x]
        ret.append(x)
    return ret

def all_except(x):
    return list([i for i in range(n) if i != x])

def dfs(cur):
    all_above = get_all_above(cur)
    all_below = []

    while True:
        go = query([cur] + all_above + all_below)

        if go in all_above:
            go = query(all_except(cur))   

        if go == cur:
            go = query(get_all_below(cur))
            return
        
        if go in all_below:
            go = query(all_except(cur))
            go = query(all_except(parent[cur]))
            return
        else:
            parent[go] = cur
            children[cur].append(go)
            dfs(go)
            all_below += get_all_below(go)

dfs(root)



