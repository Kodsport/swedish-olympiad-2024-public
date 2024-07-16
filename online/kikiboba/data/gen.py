#!/usr/bin/python3

import sys
import random
import math

def cmdlinearg(name, default=None):
    for arg in sys.argv:
        if arg.startswith(name + "="):
            return arg.split("=")[1]
    if default is None:
        print("missing parameter", name)
        sys.exit(1)
    return default

random.seed(int(cmdlinearg('seed', sys.argv[-1])))

maxN = int(cmdlinearg("maxN", 100))
n = int(cmdlinearg('n', random.randint(1,maxN)))
word = cmdlinearg("word", [])
mode = cmdlinearg("mode", "")



alfabet="qwertyuiopasdfghjklzxcvbnm"

if word:
    print(word)
    exit()

elif mode=="kiki":
    pool="qwertyuiopasdfghjklzxcvnm"#utan b
    word.append("k")
    while len(word)<n:
        word.append(pool[random.randint(0,len(pool)-1)])

elif mode=="boba":
    pool="qwertyuiopasdfghjblzxcvnm"#utan k
    word.append("b")
    while len(word)<n:
        word.append(pool[random.randint(0,len(pool)-1)])

elif mode=="boki":
    word+=["b","k"]*(random.randint(1,n//2))
    pool="qwertyuiopasdfghjlzxcvnm"#utan k och b
    while len(word)<n:
        word.append(pool[random.randint(0,len(pool)-1)])

elif mode=="none":
    pool="qwertyuiopasdfghjlzxcvnm"#utan k och b
    while len(word)<n:
        word.append(pool[random.randint(0,len(pool)-1)])

elif mode=="onlyk":
    word=["k"]*n

elif mode=="onlyb":
    word=["b"]*n

elif mode=="oneb":
    word.append("b")
    pool="qwertyuiopasdfghjlzxcvnm"#utan k och b
    while len(word)<n:
        word.append(pool[random.randint(0,len(pool)-1)])

elif mode=="onek":
    word.append("k")
    pool="qwertyuiopasdfghjlzxcvnm"#utan k och b
    while len(word)<n:
        word.append(pool[random.randint(0,len(pool)-1)])

else:
    while len(word)<n:
        word.append(alfabet[random.randint(0,len(alfabet)-1)])

random.shuffle(word)
print("".join(word))
