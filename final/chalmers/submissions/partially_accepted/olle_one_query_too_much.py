#!/usr/bin/python3

# TODO : Make sure solution does not make one extra query


up, right, downright, downleft, left = [False]*5

f = open("solution_log.txt", "w")

def read_info():
    global up, right, downright, downleft, left
    s = input()
    up, right, downright, downleft, left = [s[i] == "1" for i in range(5)]

app_calls = 0
def app():
    global app_calls
    app_calls += 1
    f.write(f"app calls: {app_calls}\n")
    print("app", flush=True)
    dist = int(input())
    f.write(f"distance: {dist}\n")
    return dist

def go(dir):
    f.write(dir + "\n")
    print(dir, flush=True)
    read_info()
    f.write("read feedback\n")

read_info()
while up:
    go("up")

distance = app()

while distance > 0:
    if distance == 1:
        go("downleft" if downleft else "downright")
        distance = app()
        if distance == 1:
            go("right")
        break

    if not (downleft and downright):
        go("downleft" if downleft else "downright")
        distance -= 1
        continue

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

f.write(f"final distance: {app()}")
print("here")