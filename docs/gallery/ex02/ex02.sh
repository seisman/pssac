#!/bin/bash
gmt pssac ../data/*.z -R200/1600/12/45 -JX15c/5c -Bx200+l'T(s)' -By5+lDegree -BWSen \
    -Ed -M1.5c -W0.5p,red > ex02.ps
rm gmt.*
