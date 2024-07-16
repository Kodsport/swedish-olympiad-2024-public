#!/usr/bin/python3

import sys
import random
import math
import os


def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=",1)[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
command = cmdlinearg("c")

args = command.split(" ")
inp = os.popen(f"pypy3 {args[0]}.py {' '.join(args[1:])} 694201337").read()

s = inp.split("\n")
j=0
if s[-1]=='':
    del s[-1]
for i in s:
    if j==0 or j==2:
        print(i)
    else:
        print(i[::-1])
    j+=1