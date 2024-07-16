#!/usr/bin/python3

up, right, downright, downleft, left = [False]*5

def read_info():
    global up, right, downright, downleft, left
    s = input()
    up, right, downright, downleft, left = [s[i] == "1" for i in range(5)]

def app():
    print("app", flush=True)
    return int(input())

def go(dir):
    print(dir, flush=True)
    read_info()

read_info()
while up:
    go("up")

dist = app()
while dist > 0:
    if downleft:
        go("downleft")
    else:
        go("downright")
    new_dist = app()
    if new_dist == dist:
        go("right")
    dist -= 1

print("here")