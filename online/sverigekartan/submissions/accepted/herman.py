#!/usr/bin/env python3

rows = int(input())
cols = int(input())
changes = int(input())

is_land = set()
is_sweden = set()

def neighbours(x, y):
    return [(x + 1, y), (x, y + 1), (x - 1, y), (x, y - 1)]

def spread_sweden(x, y):
    to_visit = [(x, y)]
    while to_visit:
        x, y = to_visit.pop()
        if (x, y) in is_land and (x, y) not in is_sweden:
            is_sweden.add((x, y))
            to_visit += neighbours(x, y)

mapdata = []
for y in range(rows):
    mapdata += [input()]

for y, row in enumerate(mapdata):
    for x, cell in enumerate(row):
        if cell != '.':
            is_land.add((x + 1, y + 1))

for y, row in enumerate(mapdata):
    for x, cell in enumerate(row):
        if cell == 'S':
            spread_sweden(x + 1, y + 1)

print(len(is_sweden))

for _ in range(changes):
    y, x = map(int, input().split())
    is_land.add((x, y))
    if any((x2, y2) in is_sweden for x2, y2 in neighbours(x, y)):
        spread_sweden(x, y)

    print(len(is_sweden))
