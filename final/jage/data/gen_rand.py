#!/usr/bin/python3

import sys
import random

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
m = int(cmdlinearg("m"))
mode = cmdlinearg("mode")

print(n, m)
letters = [chr(ord('a') + i) for i in range(ord('z')-ord('a')+1)]
names = set([
    "".join([random.choice(letters) for i in range(random.randint(5, 20))])
    for j in range(n)
    ])

while len(names) < n: # in case of duplicates generated
    names.add("".join([random.choice(letters) for i in range(random.randint(5, 20))]))

names = list(names)
random.shuffle(names)

if mode == "joshua_cheater" and "joshua" not in names:
    names[random.choice([0, random.randint(0, n - 1)])] = "joshua"


print(*names)

if mode == "rand":
    for iter in range(m):
        i = random.randint(0, n-1)
        j = random.randint(0, n-1)
        if i == j:
            j = (j + 1) % n
        print(f"{names[i]} tar {names[j]}")

elif mode == "no_cheater":
    hunter = names[0]
    other = names[1]
    for iter in range(m):
        tagged = random.choice(names)
        if n == 2:
            tagged = other
        while tagged == hunter:
            tagged = random.choice(names)
        print(f"{hunter} tar {tagged}")

        other = hunter
        hunter = tagged


elif mode == "joshua_cheater":
    cheater = "joshua"

    hunters = set([names[0], cheater])
    is_cheater = random.randint(0,1) == 1

    for iter in range(m):
        if random.randint(0, 1) == 1 and is_cheater:
            hunter = "joshua"
        else:
            hunter = hunters.pop()
        tagged = random.choice(names)
        while tagged == hunter:
            tagged = random.choice(names)
        
        print(f"{hunter} tar {tagged}")

        hunters.add(tagged)

elif mode == "few_cheaters":
    hunters = set([names[0]])
    cheater_count = random.randint(1, min(10, n//2))
    cheaters = set()
    while len(cheaters) < cheater_count:
        cheaters.add(random.choice(names))
    for cheater in cheaters:
        hunters.add(cheater)

    for iter in range(m):
        hunter = hunters.pop()
        tagged = random.choice(names)
        while tagged == hunter:
            tagged = random.choice(names)

        print(f"{hunter} tar {tagged}")

        if hunter in cheaters:
            hunters.add(hunter)
        hunters.add(tagged)