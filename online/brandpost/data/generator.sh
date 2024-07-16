#!/bin/bash
. ../../testdata_tools/gen.sh

use_solution erik.cpp

compile gen.py
compile gen_slalom.py
compile gen_bigPlanka.py

# Generate answers to sample cases
samplegroup
sample 1
sample 2


group group1 10
limits maxN=1 mode="hydrantAtStart" maxSize=10
tc g1-01 gen n=1 mode="hydrantAtStart" maxSize=10
tc g1-02 gen n=1 mode="hydrantAtStart" w=2 h=3 
tc g1-03 gen n=1 mode="hydrantAtStart" w=9 h=1
tc g1-04 gen n=1 mode="hydrantAtStart" w=10 h=10
tc g1-05 gen n=1 mode="hydrantAtStart" w=2 h=2
tc g1-06 gen n=1 mode="hydrantAtStart" w=1 h=2
tc g1-07 gen n=1 mode="hydrantAtStart" w=2 h=1

group group2 15
limits maxSize=50 maxN=50
include_group group1
tc 1
tc 2
tc g2-leftPath-01 gen n=1 maxSize=50 mode="leftPath"
tc g2-leftPath-02 gen w=50 h=50 n=50 mode="leftPath"
tc g2-rightPath-03 gen w=29 h=10 n=3 mode="rightPath"
tc g2-rightPath-04 gen w=50 h=50 n=50 mode="rightPath"
tc g2-onlyEdges-05 gen maxSize=50 maxN=10 mode="edges"
tc g2-onlyEdges-06 gen n=50 w=50 h=50 mode="edges"
tc g2-random-13 gen n=23 w=50 h=50 
tc g2-random-14 gen n=50 w=50 h=50 
tc g2-weighted-15 gen maxSize=50 maxN=50 mode="weighted"
tc g2-weighted-16 gen n=50 w=50 h=50 mode="weighted"
tc g2-linesGrid-17 gen n=20 w=50 h=1 
tc g2-linesGrid-18 gen n=21 w=1 h=50 
tc g2-linesGrid-19 gen n=22 w=49 h=2 
tc g2-linesGrid-20 gen n=23 w=2 h=49 
tc g2-filled-21 gen n=49 w=7 h=7 
tc g2-filled-22 gen n=50 w=5 h=10 
tc g2-slalom-23 gen_slalom n=50 maxSize=50
tc g2-slalom-25 gen_slalom n=50 maxSize=50 dist=5 mode="transposed"
tc g2-slalom-26 gen_slalom n=50 w=50 h=50 dist=10
tc g2-slalom-27 gen_slalom n=50 w=50 h=50 dist=10 mode="transposed"
tc g2-slalom-28 gen_slalom n=50 w=50 h=50 dist=15 length=5
tc g2-slalom-29 gen_slalom n=50 w=50 h=50 dist=15 length=7 mode="transposed"
tc g2-slalom-30 gen_slalom n=50 w=50 h=50 dist=15 length=50 
tc g2-slalom-31 gen_slalom n=50 w=50 h=10 dist=15 length=10 
tc g2-planka-32 gen_bigPlanka maxN=50 maxSize=50
tc g2-planka-33 gen_bigPlanka maxN=50 maxSize=50 mode="transposed"

group group3 17
limits maxSize=100 maxN=200
include_group group2
tc g3-leftPath-01 gen w=100 maxSize=100 maxN=200 mode="leftPath" 
tc g3-leftPath-03 gen w=100 h=100 n=179 mode="leftPath"
tc g3-rightPath-04 gen w=100 maxSize=100 maxN=200 mode="rightPath"
tc g3-rightPath-05 gen w=100 h=100 n=185 mode="rightPath"
tc g3-onlyEdges-06 gen maxSize=100 maxN=200 mode="edges"
tc g3-onlyEdges-07 gen w=100 h=100 n=198 mode="edges"
tc g3-random-09 gen n=10 w=100 h=98 
tc g3-random-11 gen n=200 w=100 h=99 
tc g3-weighted-12 gen w=80 maxSize=100 n=200 mode="weighted"
tc g3-weighted-16 gen w=100 h=100 n=200 mode="weighted"
tc g3-linesGrid-17 gen n=80 w=100 h=1 
tc g3-linesGrid-18 gen n=57 w=1 h=100 
tc g3-linesGrid-19 gen n=169 w=100 h=2 
tc g3-linesGrid-20 gen n=13 w=2 h=100 
tc g3-filled-21 gen n=200 w=20 h=10
tc g3-slalom-24 gen_slalom n=200 w=100 h=100 dist=12
tc g3-slalom-25 gen_slalom n=200 w=100 h=100 dist=13 mode="transposed"
tc g3-slalom-26 gen_slalom n=200 w=100 h=100 dist=30 length=20
tc g3-slalom-27 gen_slalom n=200 w=100 h=100 dist=31 length=21 mode="transposed"
tc g3-slalom-28 gen_slalom n=200 w=100 h=50 dist=30 length=50 
tc g3-slalom-29 gen_slalom n=200 w=100 h=60 dist=29 length=60 mode="transposed" 
tc g3-leftPath-30 gen maxSize=100 n=199 mode="leftPath"
tc g3-rightPath-31 gen maxSize=100 n=199 mode="rightPath"
tc g3-planka-32 gen_bigPlanka maxN=200 maxSize=100
tc g3-planka-33 gen_bigPlanka maxN=200 maxSize=100 mode="transposed"
tc g3-planka-34 gen_bigPlanka maxN=200 maxSize=100 width=8 height=60
tc g3-planka-35 gen_bigPlanka maxN=200 maxSize=100 height=75 width=11 mode="transposed"

group group4 27  #N=10000 w=150 h=150
limits maxSize=150 
include_group group3
tc g4-leftPath-01 gen w=150 h=150 n=270 mode="leftPath"
tc g4-rightPath-02 gen w=150 h=150 n=250 mode="rightPath"
tc g4-onlyEdges-03 gen w=150 h=150 n=500 mode="edges"
tc g4-random-04 gen w=150 h=150 maxSize=150 n=20000
tc g4-weighted-05 gen w=150 h=150 n=20000 mode="weighted"
tc g4-random-06 gen w=150 h=150 maxSize=150 n=20000
tc g4-weighted-07 gen w=150 h=150 n=20000 mode="weighted"
tc g4-filled-08 gen n=10000 w=100 h=100
tc g4-slalom-11 gen_slalom n=20000 w=150 h=150 dist=30 length=99 
tc g4-slalom-12 gen_slalom n=20000 w=150 h=70 dist=27 length=99 mode="transposed" 
tc g4-planka-13 gen_bigPlanka maxSize=150 maxN=20000
tc g4-planka-14 gen_bigPlanka maxSize=150 mode="transposed"
tc g4-planka-15 gen_bigPlanka maxSize=150 width=5 height=69
tc g4-planka-16 gen_bigPlanka maxSize=150 height=71 width=4 mode="transposed"
tc g4-planka-17 gen_bigPlanka maxSize=150 width=1 height=99


group group5 31  #try N=10000 w=1000 h=1000
include_group group4
tc g5-leftPath-01 gen w=1000 h=1000 n=20000 mode="leftPath"
tc g5-rightPath-02 gen w=1000 h=1000 n=20000 mode="rightPath"
tc g5-onlyEdges-03 gen w=1000 h=1000 n=20000 mode="edges"
tc g5-random-04 gen w=1000 h=1000 maxSize=1000 n=20000
tc g5-weighted-05 gen w=1000 h=1000 n=20000 mode="weighted"
tc g5-slalom-06 gen_slalom n=20000 w=1000 h=789 maxSize=1000
tc g5-slalom-07 gen_slalom n=20000 w=1000 h=1000 dist=91 length=150
tc g5-slalom-08 gen_slalom n=20000 w=1000 h=1000 dist=31 length=210 mode="transposed"
tc g5-slalom-09 gen_slalom n=20000 w=1000 h=1000 dist=230 length=99 
tc g5-planka-10 gen_bigPlanka maxSize=1000 maxN=20000
tc g5-planka-11 gen_bigPlanka maxSize=1000 maxN=20000 mode="transposed"
tc g5-planka-12 gen_bigPlanka maxSize=1000 maxN=20000 height=71 width=4 mode="transposed"
tc g5-planka-13 gen_bigPlanka maxSize=1000 width=1 height=99


