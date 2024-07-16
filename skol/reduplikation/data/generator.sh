#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution joshua.py

compile gen_rand.py

samplegroup
sample 1
sample 2

group group1 20
limits maxk=1
tc_manual ../manual/tc1.in
tc g1-1 gen_rand n=9 k=1
tc g1-2 gen_rand n=8 k=1
tc g1-3 gen_rand n=7 k=1
tc g1-4 gen_rand n=6 k=1

group group2 80
include_group sample
include_group group1
tc_manual ../manual/tc2.in
tc_manual ../manual/tc3.in
tc_manual ../manual/tc4.in
tc_manual ../manual/tc5.in
tc g2-1 gen_rand n=9 k=9
tc g2-2 gen_rand n=9 k=8
tc g2-3 gen_rand n=9 k=7
tc g2-4 gen_rand n=9 k=6
