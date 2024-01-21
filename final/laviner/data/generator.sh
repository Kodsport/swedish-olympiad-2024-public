#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution harry.py

compile gen_rand.py
compile gen_line.py
compile gen_resenaren.py

samplegroup
sample 1
sample 2
sample 3

group group1 10 
limits mode="line"
tc g1-01 gen_line n=100000 k=99999 
tc g1-02 gen_line n=100000 k=50000 
tc g1-03 gen_line n=100000 k=3
tc g1-04 gen_line n=100000 k=2
tc g1-05 gen_line n=100000 k=1
tc g1-06 gen_line n=2 k=1
tc g1-07 gen_line n=1000 k=13
tc g1-08 gen_line n=1000 k=1
tc g1-09 gen_line n=20 k=7
tc g1-10 gen_line n=20 k=4

group group2 10 
limits k=1 maxn=1000
tc 2
tc g1-06
tc g1-08
tc g2-rand1 gen_rand n=1000 k=1
tc g2-rand2 gen_rand n=1000 k=1
tc g2-rand3 gen_rand n=20 k=1
tc g2-rand4 gen_resenaren n=1000 k=1 modeTree="random"
tc g2-deep1 gen_resenaren n=1000 k=1 modeTree="deep"
tc g2-deeper1 gen_resenaren n=1000 k=1 modeTree="deeper"
tc g2-cube1 gen_resenaren n=1000 k=1 modeTree="killCubic"
tc g2-cube2 gen_resenaren n=999 k=1 modeTree="killCubic"
tc g2-cube3 gen_resenaren n=1000 k=1 modeTree="killCubic" root=0
tc g2-cube4 gen_resenaren n=997 k=1 modeTree="killCubic" root=0


group group3 10 
limits maxn=20
tc 1
tc 2
tc 3
tc g1-06
tc g1-09
tc g1-10
tc g2-rand3
tc g3-rand1 gen_rand n=20 k=19
tc g3-rand2 gen_rand n=20 k=13
tc g3-rand3 gen_rand n=20 k=8
tc g3-rand4 gen_rand n=20 k=3 #this is the only g3 tc that cheese.py is failing on
tc g3-rand5 gen_resenaren n=20 k=2 modeTree="random"
tc g3-deep1 gen_resenaren n=20 k=4 modeTree="deep"
tc g3-deep2 gen_resenaren n=20 k=2 modeTree="deep" root=0
tc g3-deeper1 gen_resenaren n=20 k=5 modeTree="deeper"
tc g3-deeper2 gen_resenaren n=20 k=3 modeTree="deeper"
tc g3-cube1 gen_resenaren n=20 k=3 modeTree="killCubic" root=0


group group4 15 
include_group group2
limits k=1
tc g1-05
tc g4-rand1 gen_rand n=100000 k=1
tc g4-rand2 gen_rand n=100000 k=1
tc g4-rand3 gen_resenaren n=100000 k=1 modeTree="random"
tc g4-deep1 gen_resenaren n=100000 k=1 modeTree="deep"
tc g4-deeper1 gen_resenaren n=100000 k=1 modeTree="deeper"
tc g4-cube1 gen_resenaren n=100000 k=1 modeTree="killCubic" root=0
tc g4-cube2 gen_resenaren n=99999 k=1 modeTree="killCubic"  root=0

group group5 25 
include_group group2
include_group group3
limits maxn=1000
tc g1-07
tc g5-rand1 gen_rand n=1000 k=10
tc g5-rand2 gen_rand n=1000 k=100
tc g5-rand3 gen_rand n=1000 k=999
tc g5-rand5 gen_resenaren n=1000 k=20 modeTree="random"
tc g5-deep1 gen_resenaren n=1000 k=15 modeTree="deep"
tc g5-deep2 gen_resenaren n=1000 k=45 modeTree="deep" root=0
tc g5-deeper1 gen_resenaren n=1000 k=33 modeTree="deeper"
tc g5-deeper2 gen_resenaren n=1000 k=3 modeTree="deeper" root=0
tc g5-cube1 gen_resenaren n=1000 k=15 modeTree="killCubic" root=0
#kanske något binärträd?


group group6 30
include_group group1
include_group group4 #group2
include_group group5 #group3 group2
tc g6-rand1 gen_rand n=100000 k=50000
tc g6-rand2 gen_rand n=100000 k=1000
tc g6-rand3 gen_rand n=100000 k=100
tc g6-rand4 gen_resenaren n=100000 k=20 modeTree="random"
tc g6-deep1 gen_resenaren n=100000 k=15 modeTree="deep"
tc g6-deep2 gen_resenaren n=100000 k=1234 modeTree="deep" root=0
tc g6-deeper1 gen_resenaren n=100000 k=33 modeTree="deeper"
tc g6-deeper2 gen_resenaren n=100000 k=3 modeTree="deeper" root=0
tc g6-cube1 gen_resenaren n=100000 k=321 modeTree="killCubic" root=0
tc g6-cube2 gen_resenaren n=100000 k=12345 modeTree="killCubic" root=0
