#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution cuberoot.py

compile gen_print.py

samplegroup
sample 1
sample 2
sample 3

group group1 20
limits maxn=30
tc 1
tc 2
tc g1-1 gen_print n=13
tc g1-2 gen_print n=23
tc g1-3 gen_print n=29
tc g1-4 gen_print n=25

group group2 20
limits maxn=80
include_group group1
tc g2-1 gen_print n=69
tc g2-2 gen_print n=80
tc g2-3 gen_print n=58
tc g2-4 gen_print n=60

group group3 20
limits maxn=1000
include_group group2
tc g3-1 gen_print n=1000
tc g3-2 gen_print n=992
tc g3-3 gen_print n=969
tc g3-4 gen_print n=123


group group4 20
limits maxn=100000
include_group group3
tc 3
tc g4-1 gen_print n=91081
tc g4-2 gen_print n=12345
tc g4-3 gen_print n=54321
tc g4-4 gen_print n=23584


group group5 20
include_group group4
tc g5-1 gen_print n=907038264
tc g5-2 gen_print n=123456789
tc g5-3 gen_print n=987654321
tc g5-4 gen_print n=238645623
