#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution john.py

compile gen_constrained.py
compile gen_rand.py

samplegroup
sample 1
sample 2
sample 3

group group1 20
limits l10=1
tc 2
tc_manual ../manual/m11.in
tc_manual ../manual/m12.in
tc_manual ../manual/m13.in
tc g1-1 gen_constrained choices=10 n=100000 x=2 y=20
tc g1-2 gen_constrained choices=10 n=100000 x=2 y=19


group group2 20
limits l1020=1
include_group group1
tc 3
tc_manual ../manual/m21.in
tc_manual ../manual/m22.in
tc_manual ../manual/m23.in
tc_manual ../manual/m24.in
tc g2-1 gen_constrained choices=10,20 n=100000 x=5 y=140
tc g2-2 gen_constrained choices=10,20 n=100000 x=5 y=49

group group3 20
limits maxn=500
tc 1
tc_manual ../manual/m31.in
tc g3-1 gen_constrained choices=3 n=300 x=9 y=27
tc g3-2 gen_constrained choices=11,12,13,14,15,16,17,18,19,20 n=500 x=6 y=87
tc g3-3 gen_rand n=500 hi=20 x=5 y=24
tc g3-4 gen_rand n=500 hi=20 x=5 y=47

group group4 40
include_group group2
include_group group3
tc g4-3 gen_rand n=100000 hi=20 x=5 y=24
tc g4-4 gen_rand n=100000 hi=20 x=5 y=47