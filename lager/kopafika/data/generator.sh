#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution joshua.cpp

compile gen_rand.py
compile gen_spikes.py
compile gen_killsmalltolarge.py
compile gen_killer2.py
compile kill_buyupgraded.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2

MAXC=1000000000
MAXN=200000
group group1 9
limits maxn=1000
tc 1
tc 2
tc g1-1 gen_rand n=1000 c=$MAXC mode=random
tc g1-2 gen_rand n=1000 c=$MAXC mode=random
tc g1-3 gen_rand n=1000 c=1000 mode=randomweight

group group2 12
limits maxc=50
tc 1
tc 2
tc g2-1 gen_rand n=$MAXN c=50 mode=random
tc g2-2 gen_rand n=$MAXN c=50 mode=random
tc g2-3 gen_rand n=$MAXN c=50 mode=randomweight

group group3 11 # Increasing
limits increasing=1
tc 2
tc g3-1 gen_rand n=$MAXN c=$MAXC mode=increasing
tc g3-2 gen_rand n=$MAXN c=$MAXC mode=increasing delta=1
tc g3-3 gen_rand n=$MAXN c=$MAXC mode=increasing delta=5
tc g3-4 gen_rand n=$MAXN c=$MAXC mode=increasing delta=10
tc g3-5 gen_rand n=$MAXN c=$MAXC mode=increasing delta=100

group group4 17 # Random
tc g4-1 gen_rand n=$MAXN c=$MAXC mode=random
tc g4-2 gen_rand n=$MAXN c=$MAXC mode=random
tc g4-3 gen_rand n=$MAXN c=1000 mode=random

group group5 51
include_group group1
include_group group2
include_group group3
include_group group4
tc g5-1 gen_spikes n=$MAXN c=$MAXC
tc g5-2 gen_spikes n=$MAXN c=999999999
tc g5-3 gen_spikes n=$MAXN c=972356712
tc g5-4 gen_rand   n=$MAXN c=972356712 mode=manysmall
tc g5-5 gen_killsmalltolarge
tc g5-6 gen_killer2
tc g5-7 kill_buyupgraded
