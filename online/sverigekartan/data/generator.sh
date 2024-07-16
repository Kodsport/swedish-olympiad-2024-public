#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution joshua.py

compile gen_uniform.py
compile gen_snake.py

# Generate answers to sample cases
samplegroup
limits maxr=20 maxc=20 maxq=10
sample 1
sample 2
sample 3

group group1 20
tc_manual ../poster.in

group group2 13
limits maxr=1 maxq=0
tc_manual ../manual_tests/manual_1.in
tc_manual ../manual_tests/manual_2.in
tc_manual ../manual_tests/manual_3.in
tc_manual ../manual_tests/manual_4.in
tc g2-1 gen_uniform r=1 c=10 q=0 density=0.1
tc g2-2 gen_uniform r=1 c=10 q=0 density=0.2
tc g2-3 gen_uniform r=1 c=10 q=0 density=0.3
tc g2-4 gen_uniform r=1 c=500 q=0 density=0.4
tc g2-5 gen_uniform r=1 c=500 q=0 density=0.5
tc g2-6 gen_uniform r=1 c=500 q=0 density=0.6
tc g2-7 gen_uniform r=1 c=500 q=0 density=0.7
tc g2-8 gen_uniform r=1 c=500 q=0 density=1

group group3 9
include_group group2
limits maxr=1
tc 3
tc g3-1 gen_uniform r=1 c=500 q=500 density=0.01
tc g3-2 gen_uniform r=1 c=500 q=500 density=0.05
tc g3-3 gen_uniform r=1 c=500 q=500 density=0.1
tc g3-4 gen_uniform r=1 c=500 q=500 density=0.2
tc g3-5 gen_uniform r=1 c=500 q=500 density=0.3
tc g3-6 gen_uniform r=1 c=500 q=500 density=0.4

group group4 26
include_group group1
include_group group2
limits maxq=0
tc 2
tc g4-1 gen_uniform r=500 c=500 q=0 density=0.1
tc g4-2 gen_uniform r=500 c=500 q=0 density=0.2
tc g4-3 gen_uniform r=500 c=500 q=0 density=0.3
tc g4-4 gen_uniform r=500 c=500 q=0 density=0.4
tc g4-5 gen_uniform r=500 c=500 q=0 density=0.5
tc g4-6 gen_uniform r=500 c=500 q=0 density=0.6
tc g4-7 gen_uniform r=500 c=500 q=0 density=0.7
tc g4-8 gen_uniform r=500 c=500 q=0 density=1
tc g4-9 gen_snake r=500 c=500
tc_manual ../manual_tests/manual_5.in
tc_manual ../manual_tests/manual_6.in
tc_manual ../manual_tests/manual_7.in
tc_manual ../manual_tests/manual_8.in


group group5 13
limits maxr=10 maxc=10
tc 1
tc 3
tc g5-1 gen_uniform r=10 c=10 q=100000 density=0.1
tc g5-2 gen_uniform r=10 c=10 q=100000 density=0.2
tc g5-3 gen_uniform r=10 c=10 q=100000 density=0.3
tc g5-4 gen_uniform r=10 c=10 q=100000 density=0.4
tc g5-5 gen_uniform r=10 c=10 q=100000 density=0.5
tc g5-6 gen_uniform r=10 c=10 q=100000 density=0.6
tc g5-7 gen_uniform r=10 c=10 q=100000 density=0.7
tc g5-8 gen_uniform r=10 c=10 q=0 density=1
tc g5-9 gen_snake r=10 c=10
tc g5-10 gen_snake r=10 c=10 mode=update
tc manual_5
tc manual_6
tc manual_7
tc manual_8


group group6 19
include_group group3
include_group group4
include_group group5
tc g6-1 gen_uniform r=500 c=500 q=100000 density=0.1
tc g6-2 gen_uniform r=500 c=500 q=100000 density=0.2
tc g6-3 gen_uniform r=500 c=500 q=100000 density=0.3
tc g6-4 gen_uniform r=500 c=500 q=100000 density=0.4
tc g6-5 gen_uniform r=500 c=500 q=100000 density=0.5
tc g6-6 gen_uniform r=500 c=500 q=100000 density=0.6
tc g6-7 gen_uniform r=500 c=500 q=100000 density=0.7
tc g6-8 gen_snake r=500 c=380 mode=update
