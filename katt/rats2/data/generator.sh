#!/usr/bin/env bash

PPATH=$(realpath ..)
. gen.sh

ulimit -s unlimited

use_solution olle_one_rat.py

compile generate.py

samplegroup
limits maxn=5 maxk=2
sample 1
sample 2

group group1 5
limits maxn=2 maxk=1
tc g1-1 generate n=2 k=1 seed=1
tc g1-2 generate n=2 k=1 seed=2

group group2 5
limits maxn=3 maxk=2
include_group group1
tc 1
tc g2-1 generate n=3 k=1 seed=11
tc g2-2 generate n=3 k=1 seed=12
tc g2-3 generate n=3 k=2 seed=13
tc g2-4 generate n=3 k=2 seed=14

group group3 9
limits maxn=10 maxk=9
tc 2
tc g3-1 generate n=10 k=1 seed=21
tc g3-2 generate n=10 k=1 seed=22
tc g3-3 generate n=10 k=9 seed=23
tc g3-4 generate n=10 k=8 seed=24
tc g3-5 generate n=10 k=3 seed=25
tc g3-6 generate n=10 k=4 seed=26
tc g3-7 generate n=10 k=5 seed=27
tc g3-8 generate n=10 k=2 line=1 seed=28
tc g3-9 generate n=10 k=5 line=1 seed=29
tc g3-10 generate n=10 k=9 line=1 seed=30
tc g3-11 generate n=10 k=1 star=1 seed=31
tc g3-12 generate n=10 k=3 star=1 seed=32
tc g3-13 generate n=10 k=9 star=1 seed=33

group group4 20
limits maxn=100 maxk=1
include_group group1
tc g4-1 generate n=100 k=1 seed=101
tc g4-2 generate n=99 k=1 seed=102
tc g4-3 generate n=100 k=1 seed=103
tc g4-4 generate n=93 k=1 seed=105
tc g4-5 generate n=100 k=1 seed=106
tc g4-6 generate n=100 k=1 seed=107
tc g4-7 generate n=100 k=1 line=1 seed=108
tc g4-8 generate n=100 k=1 line=1 seed=109
tc g4-9 generate n=100 k=1 star=1 seed=110
tc g4-10 generate n=100 k=1 star=1 seed=111
tc g4-11 generate n=100 k=1 star=1 seed=112

group group5 15
limits maxn=100 maxk=99
tc g5-1 generate n=100 k=25 line=1 seed=51
tc g5-2 generate n=100 k=1 line=1 seed=52
tc g5-3 generate n=100 k=51 line=1 seed=53
tc g5-4 generate n=100 k=99 line=1 seed=54
tc g5-5 generate n=100 k=10 line=1 seed=55
tc g5-6 generate n=100 k=22 line=1 seed=56
tc g5-7 generate n=100 k=80 line=1 seed=57
tc g5-8 generate n=100 k=90 line=1 seed=58
tc g5-9 generate n=100 k=2 line=1 seed=59

group group6 21
limits maxn=50 maxk=49
include_group group1
include_group group2
tc g6-1 generate n=50 k=25 seed=21
tc g6-2 generate n=50 k=10 seed=22
tc g6-3 generate n=50 k=49 seed=23
tc g6-4 generate n=50 k=3 seed=24
tc g6-5 generate n=50 k=13 seed=25
tc g6-6 generate n=50 k=49 seed=26
tc g6-7 generate n=50 k=49 seed=27
tc g6-8 generate n=50 k=10 line=1 seed=28
tc g6-9 generate n=50 k=49 line=1 seed=29
tc g6-10 generate n=50 k=15 star=1 seed=30
tc g6-11 generate n=50 k=2 star=1 seed=32
tc g6-12 generate n=50 k=4 star=1 seed=33
tc g6-13 generate n=50 k=25 star=1 seed=33
tc g6-14 generate n=50 k=20 star=1 seed=33

group group7 25
limits maxn=100 maxk=99
include_group group1
include_group group2
include_group group3
include_group group4
include_group group5
tc g7-1 generate n=100 k=99 seed=31
tc g7-2 generate n=100 k=50 seed=32
tc g7-3 generate n=100 k=11 seed=33
tc g7-4 generate n=100 k=23 seed=34
tc g7-5 generate n=100 k=10 seed=36
tc g7-6 generate n=100 k=20 seed=37
tc g7-7 generate n=100 k=90 seed=38
tc g7-8 generate n=100 k=50 seed=39
tc g7-9 generate n=100 k=80 seed=40
tc g7-10 generate n=100 k=80 star=1 seed=41
tc g7-11 generate n=100 k=10 star=1 seed=42
tc g7-12 generate n=100 k=20 star=1 seed=43
tc g7-13 generate n=100 k=40 star=1 seed=44
tc g7-14 generate n=100 k=5 star=1 seed=45
tc g7-15 generate n=100 k=99 star=1 seed=46
tc g7-16 generate n=100 k=50 star=1 seed=47

