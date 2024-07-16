#!/usr/bin/python3

import random

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

def randomMove():
    global up, right, downright, downleft, left
    s = [up, right, downright, downleft, left]
    while True:
        i = random.randint(0, 4)
        if s[i]:
            go(["up", "right", "downright", "downleft", "left"][i])
            return

read_info()
while True:
    randomMove()