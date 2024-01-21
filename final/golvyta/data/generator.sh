#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution nils.py

compile gen_rand.py
compile gen_repeat.py
compile gen_1d.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3

MAXN=300000

group group1 15
limits downright=1
limits maxn=$MAXN
tc 2
tc downright-1 gen_rand n=50 maxn=10 maxm=10 mode=random downright=1
tc downright-2 gen_rand n=$MAXN maxn=10 maxm=10 mode=random downright=1
tc downright-3 gen_rand n=$MAXN maxn=$MAXN maxm=$MAXN mode=random downright=1
tc downright-4 gen_rand n=$MAXN maxn=3 maxm=3 mode=valid downright=1
tc downright-5 gen_rand n=$MAXN maxn=100 maxm=100 mode=valid downright=1
tc downright-6 gen_rand n=$MAXN maxn=5000 maxm=5000 mode=valid downright=1
tc downright-7 gen_rand n=$MAXN maxn=$MAXN maxm=$MAXN mode=valid downright=1
tc downright-8 gen_repeat n=$MAXN c=1
tc downright-9 gen_repeat n=$(($MAXN-1)) c=$(($MAXN-1))

group group2 30
limits maxn=100
tc 1
tc 3
tc small-1 gen_rand n=1 mode=random
tc small-2 gen_rand n=10 maxn=3 maxm=3 mode=random
tc small-3 gen_rand n=100 maxn=10 maxm=10 mode=random
tc small-4 gen_rand n=100 maxn=1 maxm=1 mode=valid
tc small-5 gen_rand n=100 maxn=5 maxm=5 mode=valid
tc small-6 gen_rand n=100 maxn=33 maxm=33 mode=valid
tc small-7 gen_rand n=100 maxn=55 maxm=55 mode=valid downright=1
tc small-8 gen_1d n=100 maxn=50 p1=0.1 start=0 mode=onedirection
tc small-9 gen_1d n=100 maxn=5 p1=0.2 start=1 mode=onedirection
tc small-10 gen_1d n=100 maxn=57 p1=0.6 mode=backandforth

group group3 20
include_group group2
limits maxn=5000
tc medium-1 gen_rand n=437 mode=random
tc medium-2 gen_rand n=2132 maxn=1000 maxm=1000 mode=random
tc medium-3 gen_rand n=331 maxn=30 maxm=30 mode=valid
tc medium-4 gen_rand n=1329 maxn=210 maxm=210 mode=valid
tc medium-5 gen_rand n=5000 maxn=40 maxm=50 mode=valid
tc medium-6 gen_rand n=5000 maxn=100 maxm=1 mode=valid
tc medium-7 gen_rand n=5000 maxn=5000 maxm=5000 mode=valid
tc medium-8 gen_1d n=5000 maxn=4000 p1=0.03 start=0 mode=onedirection
tc medium-9 gen_1d n=5000 maxn=20 p1=0.1 start=1 mode=onedirection
tc medium-10 gen_1d n=5000 maxn=2997 p1=0.6 mode=backandforth
tc medium-11 gen_1d n=5000 maxn=100 p1=0.01 mode=chunks

group group4 35
include_group group3
include_group group1
limits maxn=$MAXN
tc large-1 gen_rand n=21031 maxn=1000 maxm=1000 mode=random
tc large-2 gen_rand n=$MAXN mode=random
tc large-3 gen_rand n=$MAXN mode=valid
tc large-4 gen_rand n=$MAXN maxn=3 maxm=3 mode=valid
tc large-5 gen_rand n=$MAXN maxn=1 maxm=100 mode=valid
tc large-6 gen_rand n=$MAXN maxn=300 maxm=300 mode=valid
tc large-7 gen_rand n=$MAXN maxn=5555 maxm=4 mode=valid
tc large-8 gen_rand n=$MAXN maxn=10000 maxm=10000 mode=valid
tc large-9 gen_rand n=$MAXN maxn=$MAXN maxm=$MAXN downright=1 mode=valid
tc large-10 gen_1d n=$MAXN maxn=200000 p1=0.01 start=0 mode=onedirection
tc large-11 gen_1d n=$MAXN maxn=50 p1=0.01 start=1 mode=onedirection
tc large-12 gen_1d n=$MAXN maxn=160000 p1=0.6 mode=backandforth
tc large-13 gen_1d n=$MAXN maxn=10000 p1=0.001 mode=chunks
tc large-14 gen_1d n=$MAXN maxn=600 p1=0.01 mode=chunks
tc large-15 gen_1d n=$MAXN maxn=100 p1=0.99 mode=chunks
tc large-16 gen_1d n=$MAXN maxn=10000 p1=0.0001 mode=chunks
