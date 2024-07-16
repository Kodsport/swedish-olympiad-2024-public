#!/usr/bin/python3

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


distance = app()

while distance > 0:
    go_down = min(3, distance)

    for i in range(go_down):
        go("downleft")
    
    new_distance = app()
    desired = distance - go_down

    while new_distance > desired:
        go("right")
        new_distance -= 1
    distance = new_distance

print("here")
