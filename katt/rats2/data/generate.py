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
n = int(cmdlinearg("n"))
k = int(cmdlinearg("k"))
line = int(cmdlinearg("line", "0"))
star = int(cmdlinearg("star", "0"))

print(n, k)
if line == 0 and star == 0:
    connected = set([1])
    unconnected = set([i for i in range(2, n + 1)])

    for i in range(n-1):
        a = random.choice(list(connected))
        b = random.choice(list(unconnected))
        print(a, b)
        unconnected.remove(b)
        connected.add(b)
elif line == 1:
    permutation = list([i for i in range(1, n+1)])
    random.shuffle(permutation)
    for i in range(n-1):
        print(i+1,i+2)#print(permutation[i], permutation[i+1])
elif star == 1:
    permutation = list([i for i in range(1, n+1)])
    random.shuffle(permutation)
    for i in range(n-1):
        print(permutation[0], permutation[i+1])

rats = set()
while len(rats) < k:
    r = random.randint(1, n)
    rats.add(r)

print(*sorted(list(rats)))

def get_targets():
    targets = set()
    while len(targets) < k:
        r = random.randint(1, n)
        targets.add(r)
    return targets

targets = rats
while targets == rats:
    targets = get_targets()

print(*sorted(list(targets)))