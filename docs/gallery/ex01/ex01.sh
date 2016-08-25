#!/bin/bash

gmt pssac ../data/ntkl.z -JX15c/5c -R200/1600/-6/6 -Bx200 -By2 -BWSen -Fr \
    -W0.5p -Gp+gblack+t500/700 -Gn+gred+t700/950 > ex01.ps

rm gmt.*
