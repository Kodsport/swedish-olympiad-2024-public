#!/usr/bin/python3

from collections import defaultdict

def find_cheaters(N, M, participants, tags):
    hunters = {participants[0]}
    cheaters = set()

    tagged_by = defaultdict(set)
    tagged_count = defaultdict(int)

    for tag in tags:
        # Assuming the input format is "s_i tar s_j"
        parts = tag.split(" tar ")

        if len(parts) == 2:
            hunter, tagged = parts
            tagged_by[tagged].add(hunter)
            tagged_count[hunter] += 1

            if hunter in hunters:
                hunters.remove(hunter)
                hunters.add(tagged)
            else:
                cheaters.add(hunter)
        else:
            # Handle unexpected input format
            print("Warning: Unexpected input format:", tag)

    final_cheaters = set()

    for cheater in cheaters:
        if tagged_count[cheater] > 0:
            final_cheaters.add(cheater)

    return len(final_cheaters), sorted(final_cheaters)

# Reading input
N, M = map(int, input().split())
participants = input().split()
tags = [input().strip() for _ in range(M)]

# Calling the function
num_cheaters, cheaters = find_cheaters(N, M, participants, tags)

# Printing output
print(num_cheaters)
print(*cheaters)