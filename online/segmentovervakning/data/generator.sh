#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution nils.cpp

compile gen_rand.py
compile gen_nevertwo.py
compile gen_many_collisions.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3

group group1 10
limits maxq=2
tc_manual ../manual/m1.in
tc_manual ../manual/m2.in
tc_manual ../manual/m3.in
tc_manual ../manual/m4.in
tc_manual ../manual/m5.in
tc_manual ../manual/m6.in
tc_manual ../manual/m7.in
tc_manual ../manual/m8.in
tc_manual ../manual/longSeg1.in
tc g1-1 gen_rand q=2 mode=random
tc g1-2 gen_rand q=2 mode=random

group group2 10 # Ans is 1 or -1. can't be asked to use validator.cpp for this
# Just make sure nevertwo.cpp gets 10p
tc 2
tc m1
tc m2
tc m3
tc m4
tc m5
tc m6
tc_manual ../manual/longSeg2.in
tc g2-1 gen_nevertwo q=200000 addweight=1
tc g2-2 gen_nevertwo q=200000 addweight=10
tc g2-3 gen_nevertwo q=200000 addweight=100
tc g2-collisions-1 gen_many_collisions q=200000 rem=0.1 sub2=yes
tc g2-collisions-2 gen_many_collisions q=200000 rem=0.4 sub2=yes
tc g2-collisions-3 gen_many_collisions q=200000 rem=0.57 sub2=yes
tc g2-collisions-4 gen_many_collisions q=200000 rem=0.99 sub2=yes

group group3 20
limits maxq=100
tc 1
tc 3
tc m1
tc m2
tc m3
tc m4
tc m5
tc m6
tc m7
tc m8
tc longSeg1
tc longSeg2
tc g3-1 gen_rand q=100 mode=random
tc g3-2 gen_rand q=100 mode=random remratio=1000
tc g3-3 gen_rand q=100 mode=harder
tc g3-collisions-1 gen_many_collisions q=100 unique=5
tc g3-collisions-2 gen_many_collisions q=100 unique=5 rem=0.1
tc g3-collisions-3 gen_many_collisions q=100 unique=5 rem=0.9
tc g3-collisions-4 gen_many_collisions q=100 unique=21
tc g3-collisions-5 gen_many_collisions q=100 unique=17 rem=0.7

group group4 25
include_group group3
limits maxq=2000
tc g4-1 gen_rand q=2000 mode=random
tc g4-2 gen_rand q=2000 mode=random remratio=1000
tc g4-3 gen_rand q=2000 mode=harder
tc g4-collisions-1 gen_many_collisions q=2000 unique=3 rem=0.7
tc g4-collisions-2 gen_many_collisions q=2000 unique=30 rem=0.1
tc g4-collisions-3 gen_many_collisions q=2000 unique=7 rem=0.99
tc g4-collisions-4 gen_many_collisions q=2000 unique=135 rem=0.3

group group5 35
include_group group1
include_group group2
include_group group4
tc g5-1 gen_rand q=200000 mode=random
tc g5-2 gen_rand q=200000 mode=random remratio=1000
tc g5-3 gen_rand q=200000 mode=harder
tc g5-collisions-1 gen_many_collisions q=200000 unique=5 rem=0.9
tc g5-collisions-2 gen_many_collisions q=200000 unique=15 rem=0.1
tc g5-collisions-3 gen_many_collisions q=200000 unique=155 rem=0.4
tc g5-collisions-4 gen_many_collisions q=200000 unique=250 rem=0.5
tc g5-collisions-5 gen_many_collisions q=200000 unique=2500 rem=0.49

