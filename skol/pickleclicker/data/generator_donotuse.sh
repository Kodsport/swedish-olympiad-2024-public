#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution nils.cpp

compile gen_rand.py

samplegroup
sample 1
sample 2

group group1 20
limits n=1
tc 2
tc_manual ../manual/tc1.in
tc g1-1 gen_rand n=1 t=12345 p=2
tc g1-2 gen_rand n=1 t=54321 p=3

group group2 20
limits max_t=10
tc_manual ../manual/tc2.in
tc g2-1 gen_rand n=3 t=10 p=2
tc g2-2 gen_rand n=3 t=10 p=3
tc g2-3 gen_rand n=2 t=10 p=2

group group3 20
limits max_t=1000
include_group group2
tc 1
tc_manual ../manual/tc3.in
tc g3-1 gen_rand n=4 t=1000 p=2
tc g3-2 gen_rand n=5 t=1000 p=3
tc g3-3 gen_rand n=6 t=1000 p=4
tc g3-4 gen_rand n=6 t=1000 p=5
tc g3-5 gen_rand n=6 t=1000 p=20
tc g3-6 gen_rand n=6 t=1000 p=100

group group4 40
limits max_t=100000
include_group group1
include_group group3
tc_manual ../manual/tc4.in
tc_manual ../manual/tc5.in
tc g4-1 gen_rand n=4 t=100000 p=2
tc g4-2 gen_rand n=5 t=100000 p=3
tc g4-3 gen_rand n=6 t=100000 p=4
tc g4-4 gen_rand n=6 t=100000 p=5
tc g4-5 gen_rand n=6 t=100000 p=20
tc g4-6 gen_rand n=6 t=100000 p=100
tc g4-7 gen_rand n=6 t=100000 p=1000
tc g4-8 gen_rand n=6 t=100000 p=10000
tc g4-9 gen_rand n=6 t=100000 p=3690
