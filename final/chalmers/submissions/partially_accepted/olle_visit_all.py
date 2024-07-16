#!/usr/bin/python3

import sys
sys.setrecursionlimit(100000)

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

def visit():
    if app() == 0:
        print("here")
        exit()
    if downleft:
        go("downleft")
        visit()
        go("up")
    if downright:
        go("downright")
        visit()
        go("up")

visit()