#!/usr/bin/python3

import sys
import random
import math
import os


group="""
tc g5-1 gen_hard n=100000 m=1000000 maxlen=1 perturb=0
tc g5-2 gen_hard n=100000 m=1000000 maxlen=1 perturb=0
tc g5-3 gen_aaaaa n=100000 m=1000000
tc g5-4 gen_hard n=100000 m=100 maxlen=99990
tc g5-5 gen_hard n=100000 m=4 maxlen=249995
tc g5-6 gen_hard n=100000 m=100000 maxlen=6
tc g5-7 gen_differentlen n=100000 b=0
tc g5-8 gen_differentlen n=100000 b=1
tc g5-9 gen_samelen n=100000
tc g5-10 gen_aabb n=100000 m=1000000
tc g5-11 gen_rand n=100000 m=100000 maxlen=10 alphabet_size=20
tc g5-12 gen_rand n=100000 m=100000 maxlen=10 alphabet_size=5
tc g5-13 gen_rand n=100000 m=100000 maxlen=10 alphabet_size=2

"""


for i in group.split("\n"):
    if i=="":
        continue
    s = i.split(" ")
    print(f"{s[0]} {s[1]}r rev c=\"{' '.join(s[2:])} 694201337\"")