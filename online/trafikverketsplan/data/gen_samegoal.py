#!/usr/bin/python3

import sys
import random
import math
from random import randint

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
n = int(cmdlinearg('n'))
q = int(cmdlinearg('q'))


print(n)
n-=1
cnt = 0
tail = -1
i = 1
# Long line graph 50%
while cnt < n//2:
    print(i+1,i)
    tail = i+1
    i+=1
    cnt+=1

star = []
# Star graph at bottom 40%
while cnt<n//10*9:
    print(i+1,tail)
    star.append(i+1)
    i+=1
    cnt+=1

# Some random branches pointing into star, 10%
while cnt < n:
    u = random.choice(star)
    print(i+1, u)
    star.append(i+1)
    i+=1
    cnt+=1

print(q)
for i in range(q):
    print(random.choice(star), 1)