#!/usr/bin/python3

import heapq

up, right, downright, downleft, left = [False]*5

def read_info():
    global up, right, downright, downleft, left
    s = input()
    up, right, downright, downleft, left = [s[i] == "1" for i in range(5)]

def app():
    print("app", flush=True)
    dist = int(input())
    return dist

def go(dir):
    print(dir, flush=True)
    read_info()

read_info()
while up:
    go("up")

# first query
if not (downleft and downright):
    go("downleft" if downleft else "downright")
    distance = app()
else:

    beginning = [[False]*(1<<r) for r in range(4)]
    beginning[0][0] = True
    
    def assign(i, j):
        if i == 3:
            return
        beginning[i+1][2*j] = downleft
        beginning[i+1][2*j+1] = downright
        if downleft and i < 3:
            go("downleft")
            assign(i+1, 2*j)
            go("up")
        if downright and i < 3:
            go("downright")
            assign(i+1, 2*j+1)
            go("up")
    
    assign(0,0)

    s = set()
    for i in range(4):
        for j in range(1<<i):
            if beginning[i][j]: s.add((i,j))
    
    g = {}
    for i in range(4):
        for j in range(1<<i):
            if not beginning[i][j]: continue

            key = (i,j)
            g[key] = []

            neis = [
                [(i-1, j//2), (1, 1)], 
                [(i, j-1), (0, 1)],
                [(i, j+1), (0, 1)],
                [(i+1, 2*j), (1, 1)],
                [(i+1, 2*j+1), (1, 1)],
            ]
            for nei in neis:
                dk = nei[0]
                if dk in s:
                    g[key].append(nei)

    def djikstra(start_key):
        q = []
        heapq.heapify(q)

        heapq.heappush(q, ((0,0), start_key))

        d = {x : (1e9, 1e9) for x in s}

        while not len(q) == 0:
            w, key = heapq.heappop(q)
            if w >= d[key]: continue
            d[key] = w
            stair, dis = w

            for nei, extra in g[key]:
                _s, _d = extra
                new_w = (stair + _s, dis + _d)
                heapq.heappush(q, (new_w, nei))
        return d
    
    def go_to(i, j):
        if i <= 0:
            return
        if j < (1<<(i-1)):
            go("downleft")
        else:
            go("downright")
        go_to(i-1, j%(1<<(i-1)))

    dics = {j : djikstra((3, j)) for j in range(1<<3) if beginning[3][j]}

    if len(dics) == 0:
        distance = app()
    elif len(dics) == 1:
        for j in range(1<<3):
            if beginning[3][i]:
                go_to(3, i)
                distance = app()
                break
    else:
        a = b = -1
        cands = [j for j in range(1<<3) if beginning[3][j]]
        ans = None
        for i in range(1<<3):
            if not beginning[3][i]: continue
            for j in range(i + 1, 1<<3):
                if not beginning[3][j]: continue
                test = [dics[i][(3, x)][1] - dics[j][(3, x)][1] for x in cands]
                if len(set(test)) == len(cands):
                    a = i
                    b = j
                    ans = test

        go_to(3, a)
        q1 = app()

        if q1 < 500:
            go("up")
            go("up")
            go("up")
            distance = app()
        else:
            go("up")
            go("up")
            go("up")
            go_to(3, b)
            q2 = app()
            go("up")
            go("up")
            go("up")
            
            res = ans.index(q1 - q2)
            res = cands[res]
            go_to(3, res)
            distance = q1 - dics[a][(3, res)][1]
            if distance < 0:
                go("up")
                go("up")
                go("up")
                distance = app()

while distance > 0:
    if not (downleft and downright):
        go("downleft" if downleft else "downright")
        distance -= 1
        continue

    if distance == 1:
        go("downleft" if downleft else "downright")
        distance = app()
        if distance == 1:
            go("right")
        break

    arr = [False]*4

    go("downleft")
    arr[0] = downleft
    arr[1] = downright

    go("right")
    arr[2] = downleft
    arr[3] = downright

    if not any(arr):
        print("error")

    dist = [
        [-1]*4 for i in range(4)
    ]
    for i in range(4):
        if not arr[i]: continue
        dist[i][i] = 0
        can_go_straight = True
        for j in range(i+1, 4):
            if not arr[j]: 
                can_go_straight = False
                continue
            if can_go_straight:
                dist[i][j] = dist[j][i] = j - i
            else:
                dist[i][j] = dist[j][i] = 3

    query_from = -1
    total_open = arr.count(True)
    for i in range(4):
        if not arr[i]: continue

        if len(set([d for d in dist[i] if d != -1])) == total_open:
            query_from = i

    if query_from == 3:
        go("downright")
    elif query_from == 2:
        go("downleft")
    elif query_from == 1:
        go("left")
        go("downright")
    elif query_from == 0:
        go("left")
        go("downleft")
    else:
        print("error")
    
    new_dist = app()
    wanted_dist = distance - 2
    diff = new_dist - wanted_dist

    go_to = 0
    for j in range(4):
        if dist[query_from][j] == diff:
            go_to = j
    
    go("up")
    if go_to > 1 and query_from <= 1:
        go("right")
    if go_to <= 1 and query_from > 1:
        go("left")
    go("downleft" if (go_to % 2 == 0) else "downright")
    
    distance -= 2

print("here")