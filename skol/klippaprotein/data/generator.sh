#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution joshua.cpp

compile gen_rand.py

samplegroup
sample 1
sample 2

group group1 20
limits max_k=1
tc_manual ../manual/tc1.in
tc g1-1 gen_rand n=50 k=1 alpha=1
tc g1-2 gen_rand n=50 k=1 alpha=2
tc g1-3 gen_rand n=50 k=1 alpha=5
tc g1-4 gen_rand n=50 k=1 alpha=20
tc g1-5 gen_rand n=1 k=1 alpha=1
tc g1-6 gen_rand n=2 k=1 alpha=2

group group2 20
limits ab=1
tc 2
tc g1-1
tc g1-2
tc g1-5
tc g1-6
tc_manual ../manual/tc2.in
tc g2-1 gen_rand n=50 k=1 alpha=2
tc g2-2 gen_rand n=50 k=2 alpha=2
tc g2-3 gen_rand n=50 k=5 alpha=2
tc g2-4 gen_rand n=50 k=10 alpha=2
tc g2-5 gen_rand n=50 k=40 alpha=2

group group3 60
include_group group1
include_group group2
tc 1
tc_manual ../manual/tc3.in
tc_manual ../manual/tc4.in
tc_manual ../manual/tc5.in
tc g5-1 gen_rand n=50 k=1 alpha=3
tc g5-2 gen_rand n=50 k=2 alpha=5
tc g5-3 gen_rand n=50 k=5 alpha=3
tc g5-4 gen_rand n=50 k=10 alpha=5
tc g5-5 gen_rand n=50 k=40 alpha=5
tc g5-6 gen_rand n=50 k=7 alpha=26
