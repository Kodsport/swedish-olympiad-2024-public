#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution nils.py

compile gen.py

samplegroup
sample 1
sample 2

group group1 20
limits maxn=1
tc_manual ../manual/tc1.in
tc g1-1 gen n=1 m=1 fill=1
tc g1-2 gen n=1 m=2 
tc g1-3 gen n=1 m=6 
tc g1-4 gen n=1 m=6 fill=1

group group2 40
limits fill=1
tc 2
tc_manual ../manual/tc2.in
tc_manual ../manual/tc3.in
tc g1-1
tc g1-4
tc g2-1 gen n=2 m=2 fill=1
tc g2-2 gen n=6 m=2 fill=1
tc g2-3 gen n=6 m=6 fill=1
tc g2-4 gen n=6 m=6 fill=1

group group3 40
include_group sample
include_group group1
include_group group2
tc_manual ../manual/tc4.in
tc_manual ../manual/tc5.in
tc g3-1 gen n=6 m=6
tc g3-2 gen n=5 m=6
tc g3-3 gen n=6 m=6
