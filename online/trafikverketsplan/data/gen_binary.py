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
h = int(cmdlinearg('h'))
q = int(cmdlinearg('q'))
probdown = float(cmdlinearg("prob_down"))
querymode = cmdlinearg("querymode")

n = pow(2,h)-1
print(n)
def dfs(u,p, depth):
    if p!=-1:
        if random.random() < probdown:
            print(p,u)
        else:
            print(u,p)
    if depth==h:
        return
    dfs(u*2,u,depth+1)
    dfs(u*2+1,u,depth+1)
dfs(1,-1,1)

print(q)
cnt = 0
# 10% random
while cnt < q*0.1:
    print(randint(1,n), randint(1,n))
    cnt+=1
# 90% leaves
while cnt < q:
    print(randint(n//2,n), randint(n//2,n))
    cnt+=1