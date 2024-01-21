#!/bin/bash
. ../../testdata_tools/gen.sh


ulimit -s unlimited
use_solution joshua_5k.cpp

compile gen_rand.py
compile gen_full.py
compile gen_cycle_nowalk.py
compile gen_cycle_walk.py

samplegroup
sample 1
sample 2
sample 3
sample 4

#for i in {1..100}
#do
#tc g1-$i gen_rand maxx=200
#done

group group1 20
limits maxX=100 r=0
tc 1
tc 2
tc 3
tc g1-11 gen_rand n=5 m=10 x=42 r=0
tc g1-12 gen_rand n=10 m=5 x=42 r=0
tc g1-1 gen_rand n=1000 x=100 r=0
tc g1-2 gen_rand n=15 x=100 r=0
tc g1-3 gen_rand n=20 x=100 r=0
tc g1-4 gen_rand n=30 x=100 r=0
tc g1-5 gen_rand n=60 x=100 r=0
#
tc g1-6 gen_full n=10 r=0
tc g1-7 gen_cycle_nowalk n=50 row=24 p=0 r=0
tc g1-8 gen_cycle_nowalk n=50 row=24 p=1 r=0
tc g1-9 gen_cycle_walk  n=50 row=23 p=0 r=0
tc g1-10 gen_cycle_walk n=50 row=23 p=1 r=0

group group2 5
limits maxX=5000 r=0
include_group group1
tc g2-1 gen_rand n=1000 x=5000 r=0
tc g2-2 gen_rand n=75 x=5000 r=0
tc g2-3 gen_rand n=100 x=5000 r=0
tc g2-4 gen_rand n=200 x=5000 r=0
tc g2-5 gen_rand n=300 x=5000 r=0
#
tc g2-6 gen_full n=70 r=0
tc g2-7 gen_cycle_nowalk n=1000 row=997 p=0 r=0
tc g2-8 gen_cycle_nowalk n=1000 row=997 p=1 r=0
tc g2-9 gen_cycle_walk  n=1000 row=950 p=0 r=0
tc g2-10 gen_cycle_walk n=1000 row=950 p=1 r=0

group group3 15
limits maxX=20000 r=0
include_group group2
tc g3-1 gen_rand n=1000 x=20000 r=0
tc g3-2 gen_rand n=142 x=20000 r=0
tc g3-3 gen_rand n=200 x=20000 r=0
tc g3-4 gen_rand n=400 x=20000 r=0
#
tc g3-5 gen_full n=140 r=0
tc g3-6 gen_cycle_walk n=10 m=19991 row=5 p=1 r=0

group group4 10
limits maxX=100 r=1
tc 4
tc_manual ../manual/odd.in
tc_manual ../manual/walkodd.in
tc_manual ../manual/disconnected.in
tc g4-1 gen_rand n=1000 x=100 r=1
tc g4-2 gen_rand n=15 x=100 r=1
tc g4-3 gen_rand n=20 x=100 r=1
tc g4-4 gen_rand n=30 x=100 r=1
tc g4-5 gen_rand n=60 x=100 r=1
#
tc g4-6 gen_full n=10 r=1
tc g4-11 gen_full n=9 m=11 r=1
tc g4-7 gen_cycle_nowalk n=50 row=24 p=0 r=1
tc g4-8 gen_cycle_nowalk n=50 row=24 p=1 r=1
tc g4-9 gen_cycle_walk n=50 row=23 p=0 r=1
tc g4-10 gen_cycle_walk n=50 row=23 p=1 r=1


group group5 30
limits maxX=10000 r=1
include_group group4
tc g5-1 gen_rand n=1000 x=10000 r=1
tc g5-2 gen_rand n=110 x=10000 r=1
tc g5-3 gen_rand n=200 x=10000 r=1
tc g5-4 gen_rand n=300 x=10000 r=1
tc g5-5 gen_rand n=400 x=10000 r=1
#
tc g5-6 gen_full n=100 r=1
tc g5-11 gen_full n=9 m=11 r=1
tc g5-7 gen_cycle_nowalk n=1000 row=997 p=0 r=1
tc g5-8 gen_cycle_nowalk n=1000 row=997 p=1 r=1
tc g5-9 gen_cycle_walk  n=1000 row=950 p=0 r=1
tc g5-10 gen_cycle_walk n=1000 row=950 p=1 r=1

group group6 20
limits maxX=20000 r=1
include_group group4
tc g6-1 gen_full n=140 r=1
tc g6-5 gen_full n=11 m=11 r=1
tc g6-2 gen_cycle_walk n=10 m=19950 row=5 p=0 r=1
tc g6-3 gen_cycle_walk n=10 m=19950 row=5 p=1 r=1
tc g6-4 gen_cycle_walk n=10 m=19991 row=5 p=1 r=1
tc g6-7 gen_cycle_nowalk n=10 m=19949 row=5 p=0 r=1
tc g6-8 gen_cycle_nowalk n=10 m=19949 row=5 p=1 r=1
