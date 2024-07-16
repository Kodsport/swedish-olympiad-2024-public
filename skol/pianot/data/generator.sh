#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution joshua_dp.cpp

compile gen_rand.py

samplegroup
limits max=5
sample 1
sample 2

group group1 20
limits max=8
include_group sample
tc_manual ../manual/tc1.in
tc g1-1 gen_rand n=200 alpha=8
tc g1-2 gen_rand n=32 alpha=8
tc g1-3 gen_rand n=16 alpha=8
tc g1-4 gen_rand n=1 alpha=8
tc g1-5 gen_rand n=2 alpha=8
tc_manual ../manual/2letters.in
tc_manual ../manual/allSame.in

group group2 80
limits max=15
include_group group1
tc_manual ../manual/tc2.in
tc_manual ../manual/tc3.in
tc_manual ../manual/tc4.in
tc_manual ../manual/tc5.in
tc g2-1 gen_rand n=50 alpha=15
tc g2-2 gen_rand n=100 alpha=15
tc g2-3 gen_rand n=200 alpha=15
