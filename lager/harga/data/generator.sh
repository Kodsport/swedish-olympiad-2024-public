#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution nils.cpp

compile gen_rand.py
compile gen_repeat.py
compile gen_identity.py
compile gen_valid.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3
sample 4

MAXN=300000

group group1 10
limits maxn=$MAXN
tc 1
tc one-1 gen_rand n=1 m=10
tc one-2 gen_rand n=1 m=1
tc one-3 gen_rand n=1 m=$MAXN mode=permutation
tc one-4 gen_rand n=1 m=$MAXN
tc one-5 gen_repeat n=1 m=$MAXN chain=1
tc one-6 gen_repeat n=1 m=$MAXN chain=100000
tc one-7 gen_repeat n=1 m=$MAXN chain=299999
tc one-8 gen_repeat n=1 m=$MAXN chain=100000 mode=invalid
tc one-9 gen_valid n=1 m=$MAXN cycles=1 mode=unicycle
tc one-10 gen_valid n=1 m=$MAXN cycles=2 mode=cycles
tc one-11 gen_repeat n=1 m=$MAXN chain=150000 mode=disconnected

group group2 17
limits identity=1
limits maxn=$MAXN
tc 4
tc identity-1 gen_rand n=1 m=10 mode=identity
tc identity-2 gen_rand n=300 m=300 mode=identity
tc identity-3 gen_rand n=300 m=30 mode=identity
tc identity-4 gen_identity n=$MAXN m=100000 mode=random
tc identity-5 gen_identity n=$MAXN m=10000 mode=sorted
tc identity-6 gen_identity n=$MAXN m=10000 mode=cycle1
tc identity-7 gen_identity n=$MAXN m=300 mode=cycle2
tc identity-8 gen_identity n=$MAXN m=10000 mode=cycle2
tc identity-9 gen_identity n=$MAXN m=100000 mode=cycle2
tc identity-10 gen_identity n=299999 m=$MAXN mode=cycle2

group group3 16
limits maxn=300
tc 2
tc 3
tc 4
tc small-1 gen_rand n=10 m=10 mode=random
tc small-2 gen_rand n=10 m=10 mode=permutation
tc small-3 gen_rand n=300 m=30 mode=permutation
tc small-4 gen_rand n=300 m=30 mode=chain chain=1
tc small-5 gen_rand n=300 m=30 mode=chain chain=10
tc small-6 gen_rand n=100 m=30 mode=permutation
tc small-7 gen_repeat n=300 m=300
tc small-8 gen_repeat n=300 m=300 chain=100
tc small-9 gen_repeat n=300 m=300 chain=100 mode=invalid
tc small-10 gen_identity n=300 m=20 mode=cycle2
tc small-11 gen_valid n=299 m=300 mode=random
tc small-12 gen_valid n=299 m=300 mode=random
tc small-13 gen_valid n=299 m=300 mode=unicycle cycles=177
tc small-14 gen_valid n=299 m=300 mode=cycles cycles=100
tc small-15 gen_valid n=299 m=300 mode=equal_cycles cycles=50
tc small-16 gen_valid n=101 m=300 mode=equal_cycles cycles=100
tc small-17 gen_valid n=299 m=300 mode=equal_cycles_random cycles=100
tc small-18 gen_repeat n=300 m=300 chain=150 mode=disconnected

group group4 22
limits maxn=3000
limits permutation=1
tc 4
tc perm-1 gen_rand n=300 m=30 mode=permutation
tc perm-2 gen_repeat n=3000 m=3000
tc perm-3 gen_identity n=3000 m=100 mode=cycle2
tc perm-4 gen_rand n=3000 m=10 mode=permutation
tc perm-5 gen_rand n=3000 m=2000 mode=permutation
tc perm-6 gen_valid n=2999 m=3000 mode=random
tc perm-7 gen_valid n=2989 m=3000 mode=unicycle cycles=10
tc perm-8 gen_valid n=2989 m=3000 mode=cycles cycles=100
tc perm-9 gen_valid n=2989 m=3000 mode=cycles cycles=2000
tc perm-10 gen_valid n=2989 m=3000 mode=unicycle cycles=2000
tc perm-11 gen_valid n=2989 m=3000 mode=equal_cycles cycles=500
tc perm-12 gen_valid n=2989 m=3000 mode=equal_cycles cycles=1500
tc perm-13 gen_valid n=2989 m=3000 mode=equal_cycles_random cycles=500

group group5 9
include_group group4
include_group group3
limits maxn=3000
tc medium-1 gen_rand n=300 m=30 mode=chain chain=1
tc medium-2 gen_rand n=300 m=300 mode=chain chain=10
tc medium-3 gen_rand n=300 m=40 mode=chain chain=20
tc medium-4 gen_repeat n=3000 m=3000 chain=3
tc medium-5 gen_repeat n=3000 m=3000 chain=1500 mode=invalid
tc medium-7 gen_repeat n=3000 m=3000 chain=2987
tc medium-8 gen_rand n=3000 m=3000
tc medium-10 gen_repeat n=3000 m=3000 chain=1500 mode=disconnected

group group6 26
include_group group5
include_group group1
include_group group2
limits maxn=$MAXN
tc large-1 gen_rand n=$MAXN m=$MAXN
tc large-2 gen_rand n=$MAXN m=1000 mode=permutation
tc large-3 gen_repeat n=$MAXN m=$MAXN
tc large-4 gen_repeat n=$MAXN m=$MAXN chain=150000
tc large-5 gen_repeat n=$MAXN m=$MAXN chain=150000 mode=invalid
tc large-6 gen_valid n=299993 m=$MAXN mode=random
tc large-7 gen_valid n=299999 m=$MAXN mode=random
tc large-8 gen_valid n=299999 m=$MAXN mode=unicycle cycles=10
tc large-9 gen_valid n=299999 m=$MAXN mode=unicycle cycles=400
tc large-10 gen_valid n=299999 m=$MAXN mode=unicycle cycles=250000
tc large-11 gen_valid n=299999 m=$MAXN mode=cycles cycles=10
tc large-12 gen_valid n=299999 m=$MAXN mode=cycles cycles=10000
tc large-13 gen_valid n=299999 m=$MAXN mode=equal_cycles cycles=10000
tc large-14 gen_valid n=299999 m=$MAXN mode=equal_cycles cycles=150000
tc large-15 gen_valid n=299999 m=$MAXN mode=equal_cycles_random cycles=20000
tc large-16 gen_valid n=299997 m=$MAXN mode=equal_cycles_random cycles=10000
