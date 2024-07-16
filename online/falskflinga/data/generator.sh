#!/bin/bash
REQUIRE_SAMPLE_REUSE=0
. ../../testdata_tools/gen.sh

use_solution olle.py

compile gen_rand.py
compile gen_from_flake.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2


group group1 20
limits n=7
tc 2
tc g1-random-1 gen_rand n=7
tc g1-random-2 gen_rand n=7
tc g1-random-3 gen_rand n=7
tc g1-random-4 gen_rand n=7
tc g1-random-5 gen_rand n=7
tc g1-random-6 gen_rand n=7
tc g1-random-7 gen_rand n=7
tc g1-random-8 gen_rand n=7
tc g1-random-9 gen_rand n=7
tc g1-random-10 gen_rand n=7
tc g1-flake-1 gen_from_flake n=7
tc g1-flake-2 gen_from_flake n=7
tc g1-flake-3 gen_from_flake n=7
tc g1-flake-5 gen_from_flake n=7

group group2 20
limits n=11
tc g2-random-1 gen_rand n=11
tc g2-random-2 gen_rand n=11
tc g2-random-3 gen_rand n=11
tc g2-random-4 gen_rand n=11
tc g2-random-5 gen_rand n=11
tc g2-random-6 gen_rand n=11
tc g2-random-7 gen_rand n=11
tc g2-random-8 gen_rand n=11
tc g2-random-9 gen_rand n=11
tc g2-random-10 gen_rand n=11
tc g2-flake-1 gen_from_flake n=11
tc g2-flake-2 gen_from_flake n=11
tc g2-flake-3 gen_from_flake n=11
tc g2-flake-4 gen_from_flake n=11
tc g2-flake-5 gen_from_flake n=11

group group3 60
limits n=15
tc g3-random-1 gen_rand n=15
tc g3-random-2 gen_rand n=15
tc g3-random-3 gen_rand n=15
tc g3-random-4 gen_rand n=15
tc g3-random-5 gen_rand n=15
tc g3-random-6 gen_rand n=15
tc g3-random-7 gen_rand n=15
tc g3-random-8 gen_rand n=15
tc g3-random-9 gen_rand n=15
tc g3-random-10 gen_rand n=15
tc g3-flake-1 gen_from_flake n=15
tc g3-flake-2 gen_from_flake n=15
tc g3-flake-3 gen_from_flake n=15
tc g3-flake-4 gen_from_flake n=15
tc g3-flake-5 gen_from_flake n=15
tc g3-flake-6 gen_from_flake n=15
tc g3-flake-7 gen_from_flake n=15
tc g3-flake-8 gen_from_flake n=15
tc g3-flake-9 gen_from_flake n=15
tc g3-flake-10 gen_from_flake n=15
tc g3-flake-11 gen_from_flake n=15
tc g3-flake-12 gen_from_flake n=15
tc g3-flake-13 gen_from_flake n=15
tc g3-flake-14 gen_from_flake n=15
tc g3-flake-15 gen_from_flake n=15
tc g3-flake-16 gen_from_flake n=15
tc g3-flake-17 gen_from_flake n=15
tc g3-flake-18 gen_from_flake n=15
tc g3-flake-19 gen_from_flake n=15
tc g3-flake-20 gen_from_flake n=15
tc g3-flake-21 gen_from_flake no_stem=1 n=15
tc g3-flake-22 gen_from_flake no_stem=1 n=15
tc g3-flake-23 gen_from_flake no_stem=1 n=15
tc g3-flake-24 gen_from_flake no_stem=1 n=15
tc g3-flake-25 gen_from_flake no_stem=1 n=15
tc g3-flake-26 gen_from_flake no_stem=1 n=15
tc g3-flake-27 gen_from_flake no_stem=1 n=15
tc g3-flake-28 gen_from_flake no_stem=1 n=15
tc g3-flake-29 gen_from_flake no_stem=1 n=15
tc g3-flake-30 gen_from_flake no_stem=1 n=15