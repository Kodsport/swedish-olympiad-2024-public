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

# Choose one branch. We will direct all edges upwards in it, all others downwards.
# All starting points for queries will be on this branch 

random.seed(int(cmdlinearg('seed', sys.argv[-1])))
h = int(cmdlinearg('h'))
q = int(cmdlinearg('q'))

n = pow(2,h)-1
print(n)
def dfs(u,p, depth,allleft):
    if p!=-1:
        if allleft:
            print(u,p)
        else:
            print(p,u)
    if depth==h:
        return
    dfs(u*2,u,depth+1,allleft)
    dfs(u*2+1,u,depth+1,False)
dfs(1,-1,1,True)

leftbranch = [1]
while leftbranch[-1] < n:
    leftbranch.append(leftbranch[-1]*2)
del leftbranch[-1]
t=sum(leftbranch)
w = [((t-i)/t)**1.5 for i in leftbranch]

print(q)
cnt = 0
for i in range(q):
    print(random.choices(leftbranch, weights=w, k=1)[0], random.randint(n//2,n))