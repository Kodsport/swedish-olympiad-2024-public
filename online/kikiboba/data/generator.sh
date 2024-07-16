#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution harry.py

compile gen.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3
sample 4

group group1 20
limits maxN=1
tc g1-01 gen word="t"
tc g1-02 gen word="y"
tc g1-03 gen word="r"
tc g1-04 gen word="u"
tc g1-05 gen word="e"
tc g1-06 gen word="i"
tc g1-07 gen word="w"
tc g1-08 gen word="o"
tc g1-09 gen word="q"
tc g1-10 gen word="p"
tc g1-11 gen word="a"
tc g1-12 gen word="s"
tc g1-13 gen word="d"
tc g1-14 gen word="f"
tc g1-15 gen word="g"
tc g1-16 gen word="h"
tc g1-17 gen word="j"
tc g1-18 gen word="k"
tc g1-19 gen word="l"
tc g1-20 gen word="z"
tc g1-21 gen word="m"
tc g1-22 gen word="x"
tc g1-23 gen word="n"
tc g1-24 gen word="c"
tc g1-25 gen word="b"
tc g1-26 gen word="v"

group group2 50
limits mode="bORk"
tc 1
tc 2
tc g1-25
tc g1-18
tc g2-01 gen n=5 mode="boba"
tc g2-02 gen n=2 mode="boba"
tc g2-03 gen n=15 mode="boba"
tc g2-04 gen n=97 mode="boba"
tc g2-05 gen n=3 mode="kiki"
tc g2-06 gen n=22 mode="kiki"
tc g2-07 gen n=69 mode="kiki"
tc g2-08 gen n=98 mode="kiki"
tc g2-09 gen mode="onlyb"
tc g2-10 gen mode="onlyk"
tc g2-11 gen mode="onlyb"
tc g2-12 gen mode="onlyk"
tc g2-13 gen mode="oneb"
tc g2-14 gen mode="onek"
tc g2-15 gen n=100 mode="boba"
tc g2-16 gen n=100 mode="kiki"
tc g2-17 gen n=100 mode="onlyk"
tc g2-18 gen n=100 mode="onlyb"
tc g2-19 gen n=100 mode="oneb"
tc g2-20 gen n=100 mode="onek"

group group3 30
include_group group1
include_group group2
tc 3
tc 4
tc g3-01 gen n=3 mode="boki"
tc g3-02 gen n=2 mode="boki"
tc g3-03 gen mode="boki"
tc g3-04 gen mode="boki"
tc g3-05 gen n=99 mode="boki"
tc g3-06 gen n=100 mode="boki"
tc g3-07 gen n=3 mode="none"
tc g3-08 gen n=2 mode="none"
tc g3-09 gen mode="none"
tc g3-10 gen mode="none"
tc g3-11 gen n=99 mode="none"
tc g3-12 gen n=100 mode="none"
tc g3-13 gen mode="none"
tc g3-14 gen mode="boki"
tc g3-15 gen mode="none"
tc g3-16 gen mode="boki"
tc g3-17 gen mode="none"
tc g3-18 gen mode="boki"
tc g3-19 gen mode="boki"
tc g3-20 gen 

