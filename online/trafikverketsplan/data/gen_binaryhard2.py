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
leftside = []
rightside = []
def dfs(u,p, depth,up):
    if up:
        leftside.append(u)
    else:
        rightside.append(u)
    if p!=-1:
        if up or (depth>12 and random.random()>0.99): # Make the tree not completely uniform
            print(u,p)
        else:
            print(p,u)
    if depth==h:
        return
    dfs(u*2,u,depth+1,up)
    dfs(u*2+1,u,depth+1,up)
dfs(2,1,2,True)
dfs(3,1,2,False)

print(q)

cnt = 0
# 10% random
while cnt < q*0.1:
    print(randint(1,n), randint(1,n))
    cnt+=1
# 90% leftright
while cnt < q:
    print(random.choice(leftside), random.choice(rightside))
    cnt+=1
