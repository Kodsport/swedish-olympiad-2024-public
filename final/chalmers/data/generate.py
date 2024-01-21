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
t = int(cmdlinearg('type'))

if t == 1:
    n = int(cmdlinearg('n')) # how many floors total
    c = int(cmdlinearg('c')) # how many floors in copy struct
    r = int(cmdlinearg('r')) # how many rooms to remove

    room = [[1 for i in range(1<<level)] for level in range(c)]
    removed = 0
    iterations = 0
    while removed < r:
        iterations += 1
        L = random.randint(1, c-1)
        OFFSET = random.randint(0, 1<<L-1)

        if iterations > 100:
            break
        if room[L][OFFSET] == 0:
            continue
        if room[L].count(1) == 1:
            continue
        


        a = b = OFFSET
        revert = {}
        for level in range(L, c):
            revert[level] = {}
            for j in range(a, b + 1):
                revert[level][j] = room[level][j]
                room[level][j] = 0
            a = 2 * a
            b = 2 * b + 1
        if any([all(room[level][j] == 0 for j in range(1<<level)) for level in range(c)]):
            for level in revert:
                for j in revert[level]:
                    room[level][j] = revert[level][j]
        removed += 1
    
    A = random.randint(max(1, n - 5), n - 1)
    B = n - 1
    
    def gen_path(x):
        path = []
        relative_level = 0
        offset = 0

        for i in range(x):
            go = random.randint(0, 1)
            if relative_level == c - 1:
                relative_level = 0
                offset = 0
                go = 0
            else:
                if room[relative_level+1][2*offset+go] == 0:
                    go = 1 - go
                if room[relative_level+1][2*offset+go] == 0:
                    return path
                relative_level += 1
                offset = 2*offset + go
            path.append(go)
        return path

    path_start = gen_path(A)
    A = len(path_start)
    path_goal = gen_path(B)
    B = len(path_goal)
    print(t)
    print(c, n)
    for level in range(c):
        print(*room[level])
    
    print(A)
    print(*path_start)
    print(B)
    print(*path_goal)

elif t == 2:
    n = int(cmdlinearg('n')) # how many floors total
    A = random.randint(max(1, n-5), n-1)
    path = [1] + [random.choice([0,1]) for i in range(A-1)]

    B = n-1
    goal = [0]*B

    print(2)
    print(n)
    print(A)
    print(*path)
    print(B)
    print(*goal)