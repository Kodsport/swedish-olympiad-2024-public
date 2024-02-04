#!/bin/bash
. ../../testdata_tools/gen.sh

ulimit -s unlimited
use_solution joshua.cpp

compile gen_random.py
compile gen_bounded.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3

group group1 5
limits onlyRight=1

tc g1-smallN gen_random n=15 k=5 onlyRight=1 
tc g1-smallN_bigDist gen_random n=15 k=5 onlyRight=1 dist=10000000 
tc g1-k1 gen_random n=100000 k=1 onlyRight=1 
tc g1-n1500 gen_random n=1500 k=500 onlyRight=1 
tc g1-n2000 gen_random n=2000 k=1000 onlyRight=1 dist=10000
tc g1-bounded gen_bounded n=10000 k=5000 bounded=1 onlyRight=1
tc g1-max1 gen_random n=100000 k=50000 onlyRight=1 dist=49 
tc g1-max2 gen_random n=100000 k=100000 onlyRight=1 dist=1000
tc g1-max3 gen_random n=100000 k=99998 onlyRight=1 dist=69
tc g1-singleBranch gen_bounded n=10000 k=50 onlyRight=1 branches=1
tc_manual ../manual/coverAll_n1_right.in

group group2 5
limits maxk=1
tc 2 
tc g1-k1
tc coverAll_n1_right
tc g2-smallN gen_random n=15 k=1 dist=10000001 branches=10
tc g2-singleBranch gen_bounded n=100000 k=1 branches=1
tc g2-bounded gen_bounded n=10000 k=1 bounded=1
tc g2-max1 gen_random n=100000 k=1 dist=1000 
tc g2-max2 gen_bounded n=100000 k=1 
tc_manual ../manual/coverAll_n1.in
tc_manual ../manual/coverAll_n2.in


group group3 7
limits maxn=15
tc 1
tc 3
tc g1-smallN
tc g1-smallN_bigDist
tc coverAll_n1_right
tc g2-smallN
tc coverAll_n1
tc coverAll_n2
tc_manual ../manual/greedyKiller_n3.in
tc g3-singleBranch gen_bounded n=15 k=6 branches=1
tc g3-max gen_random n=15 k=7 dist=10000002 branches=10
tc g3-max2 gen_random n=15 k=15 dist=10000002 branches=10
tc g3-bounded gen_bounded n=15 k=8 bounded=1 branches=10
tc g3-max3 gen_bounded n=15 k=14 branches=10 bounded=1
tc g3-max4 gen_bounded n=15 k=2 branches=10 bounded=1
tc g3-max5 gen_bounded n=15 k=3 branches=10 bounded=1
tc g3-max6 gen_bounded n=15 k=4 branches=10 bounded=1
tc g3-max7 gen_bounded n=15 k=13 branches=10 bounded=1
tc g3-max8 gen_random n=15 k=5 dist=10000003 branches=10
tc_manual ../manual/coverAll_n4.in

group group4 11
limits maxn=2000 bounded=1
tc 1
tc 2
tc 3
tc g1-smallN
tc g1-n1500
tc g3-bounded
tc g3-max3
tc g3-max4
tc g3-max5
tc g3-max6
tc g3-max7
tc g4-01 gen_bounded n=2000 k=1000 bounded=1 branches=8
tc g4-02 gen_bounded n=2000 k=2000 bounded=1 branches=10
tc g4-03 gen_bounded n=2000 k=1643 bounded=1 branches=10
tc g4-04 gen_bounded n=2000 k=1998 bounded=1 branches=10
tc g4-05 gen_random n=2000 k=1234 dist=10 branches=10
tc g4-06 gen_random n=2000 k=500 dist=10 branches=10
tc g4-07 gen_bounded n=2000 k=500 bounded=1 branches=10
tc g4-08 gen_bounded n=2000 k=678 bounded=1 branches=1
tc g4-09 gen_bounded n=2000 k=51 bounded=1 branches=10
tc g4-10 gen_bounded n=2000 k=17 bounded=1 branches=10
tc g4-11 gen_bounded n=2000 k=3 bounded=1 branches=10
tc_manual ../manual/greedyKiller_n1000.in
tc_manual ../manual/greedyKiller2_n1000.in

group group5 23
limits maxn=2000
include_group group3
include_group group4
tc g1-smallN_bigDist
tc g1-n2000
tc g5-01 gen_bounded n=2000 k=1000 branches=10
tc g5-02 gen_bounded n=2000 k=1999 branches=10
tc g5-03 gen_bounded n=2000 k=2000 branches=10
tc g5-04 gen_random n=2000 k=1984 dist=100000 branches=10
tc g5-05 gen_random n=2000 k=512 dist=1000 branches=10
tc g5-06 gen_random n=2000 k=51 dist=1000 branches=10
tc g5-07 gen_bounded n=2000 k=3 branches=10
tc g5-08 gen_bounded n=2000 k=1551 branches=10

group group6 31 #If it's bounded by 10^5, and no 2 trees are touching, then, n can't be more than 33333...
limits bounded=1
include_group group4 
tc g1-bounded
tc g2-bounded
tc g6-01 gen_bounded n=10000 k=1000 bounded=1
tc g6-02 gen_bounded n=20000 k=5000 bounded=1
tc g6-03 gen_bounded n=23456 k=12345 bounded=1
tc g6-04 gen_bounded n=30333 k=20345 bounded=1
tc g6-05 gen_bounded n=30333 k=30000 bounded=1
tc g6-06 gen_bounded n=33333 k=33333 bounded=1
tc g6-07 gen_bounded n=20500 k=10250 bounded=1 
tc g6-08 gen_bounded n=60000 k=30000 bounded=1 
tc g6-09 gen_bounded n=60000 k=56789 bounded=1 
tc g6-10 gen_random n=12345 k=1984 dist=8 branches=10
tc g6-11 gen_bounded n=60001 k=2000 bounded=1 
tc g6-12 gen_bounded n=60001 k=43512 bounded=1 
tc g6-13 gen_bounded n=60001 k=131 bounded=1 
tc g6-14 gen_bounded n=60001 k=13 bounded=1 

group group7 18
include_group group1
include_group group2
include_group group3
include_group group4
include_group group5
include_group group6
tc g7-01 gen_bounded n=100000 k=1000 
tc g7-02 gen_bounded n=100000 k=50000 
tc g7-03 gen_bounded n=100000 k=99911
tc g7-04 gen_bounded n=100000 k=100000
tc g7-05 gen_random n=100000 k=56789 dist=100 branches=5
tc g7-06 gen_random n=100000 k=123 dist=10 branches=5
tc g7-07 gen_random n=100000 k=3 dist=10 branches=5
tc g7-08 gen_bounded n=100000 k=32 
tc g7-09 gen_bounded n=100000 k=76567 
tc g7-10 gen_bounded n=100000 k=33333
