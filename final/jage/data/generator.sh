#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution olle.py

compile gen_rand.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3
sample 4

MAXN=100000
MAXM=100000

group group1 10
limits maxn=$MAXN
limits maxm=1
tc g1-1 gen_rand n=$MAXN m=1 mode=rand seed=1
tc g1-2 gen_rand n=$MAXN m=1 mode=rand seed=2
tc g1-3 gen_rand n=$MAXN m=1 mode=rand seed=3
tc g1-4 gen_rand n=$MAXN m=1 mode=no_cheater seed=4
tc g1-5 gen_rand n=$MAXN m=1 mode=no_cheater seed=5
tc g1-6 gen_rand n=$MAXN m=1 mode=no_cheater seed=6
tc g1-7 gen_rand n=100 m=1 mode=rand seed=7
tc g1-8 gen_rand n=100 m=1 mode=rand seed=8
tc g1-9 gen_rand n=100 m=1 mode=rand seed=9
tc g1-10 gen_rand n=100 m=1 mode=rand seed=10
tc g1-11 gen_rand n=100 m=1 mode=no_cheater seed=11
tc g1-12 gen_rand n=100 m=1 mode=no_cheater seed=12
tc g1-13 gen_rand n=100 m=1 mode=no_cheater seed=13
tc g1-14 gen_rand n=100 m=1 mode=no_cheater seed=14
tc_manual ../manual/joshuam1n2.in
tc_manual ../manual/boshuam1n2.in

group group2 15
limits maxn=2
limits maxm=$MAXM
tc g2-1 gen_rand n=2 m=$MAXM mode=rand seed=15
tc g2-2 gen_rand n=2 m=$MAXM mode=rand seed=16
tc g2-3 gen_rand n=2 m=$MAXM mode=rand seed=17
tc g2-4 gen_rand n=2 m=$MAXM mode=rand seed=18
tc g2-5 gen_rand n=2 m=$MAXM mode=no_cheater seed=19
tc g2-6 gen_rand n=2 m=$MAXM mode=no_cheater seed=20
tc g2-7 gen_rand n=2 m=$MAXM mode=no_cheater seed=21
tc g2-8 gen_rand n=2 m=$MAXM mode=no_cheater seed=22
tc_manual ../manual/joshuam2n2.in
tc_manual ../manual/boshuam2n2.in
tc joshuam1n2
tc boshuam1n2

group group3 15
limits maxn=$MAXN
limits maxm=$MAXM
tc g3-1 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=23
tc g3-2 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=24
tc g3-3 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=25
tc g3-4 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=26
tc g3-5 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=27
tc g3-6 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=28
tc g3-7 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=29
tc g3-8 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=30
tc g3-9 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=31
tc g3-10 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=32
tc g3-11 gen_rand n=$MAXN m=$MAXM mode=joshua_cheater seed=33
tc joshuam2n2
tc joshuam1n2

group group4 20
include_group group2
limits maxn=200
tc g4-1 gen_rand n=200 m=$MAXM mode=rand seed=34
tc g4-2 gen_rand n=200 m=$MAXM mode=rand seed=35
tc g4-3 gen_rand n=200 m=$MAXM mode=rand seed=36
tc g4-4 gen_rand n=200 m=$MAXM mode=rand seed=37
tc g4-5 gen_rand n=200 m=$MAXM mode=few_cheaters seed=38
tc g4-6 gen_rand n=200 m=$MAXM mode=few_cheaters seed=39
tc g4-7 gen_rand n=200 m=$MAXM mode=few_cheaters seed=40
tc g4-8 gen_rand n=200 m=$MAXM mode=few_cheaters seed=41
tc g4-9 gen_rand n=200 m=$MAXM mode=no_cheater seed=42
tc g4-10 gen_rand n=200 m=$MAXM mode=no_cheater seed=43
tc g4-11 gen_rand n=200 m=$MAXM mode=rand seed=44
tc g4-12 gen_rand n=200 m=$MAXM mode=rand seed=45

group group5 40
tc 1
tc 2
tc 3
tc 4
include_group group1
include_group group2
include_group group3
include_group group4
limits maxn=$MAXN
limits maxm=$MAXM
tc g5-1 gen_rand n=$MAXN m=$MAXM mode=rand seed=46
tc g5-2 gen_rand n=$MAXN m=$MAXM mode=rand seed=47
tc g5-3 gen_rand n=$MAXN m=$MAXM mode=rand seed=48
tc g5-4 gen_rand n=$MAXN m=$MAXM mode=rand seed=49
tc g5-5 gen_rand n=$MAXN m=$MAXM mode=rand seed=50
tc g5-6 gen_rand n=$MAXN m=$MAXM mode=rand seed=51
tc g5-7 gen_rand n=$MAXN m=$MAXM mode=rand seed=52
tc g5-8 gen_rand n=$MAXN m=$MAXM mode=rand seed=53
tc g5-9 gen_rand n=$MAXN m=$MAXM mode=rand seed=54
tc g5-10 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=55
tc g5-11 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=56
tc g5-12 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=57
tc g5-13 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=58
tc g5-14 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=59
tc g5-15 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=60
tc g5-16 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=61
tc g5-17 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=62
tc g5-18 gen_rand n=$MAXN m=$MAXM mode=no_cheater seed=63
tc g5-19 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=64
tc g5-20 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=65
tc g5-21 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=66
tc g5-22 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=67
tc g5-23 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=68
tc g5-24 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=69
tc g5-25 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=70
tc g5-26 gen_rand n=$MAXN m=$MAXM mode=few_cheaters seed=71

