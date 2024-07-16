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

while True:
    go("up")