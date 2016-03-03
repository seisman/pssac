#!/bin/bash
PS=test-T.ps

gmt set PS_MEDIA 21cx32c
gmt pssac ntkl.z onkl.z -JX15c/4c -R200/1600/22/27 -Bx100 -By1 -BWSen -Ed -M1.5c -K -P > $PS
gmt pssac ntkl.z onkl.z -JX15c/4c -R0/1400/22/27 -Bx100 -By1 -BWSen -Ed -M1.5c -K -O -Y5c -T+t-5 >> $PS
gmt pssac ntkl.z onkl.z -JX15c/4c -R-500/500/22/27 -Bx100 -By1 -BWSen -Ed -M1.5c -K -O -Y5c -T+t1 >> $PS
gmt pssac ntkl.z onkl.z -JX15c/4c -R0/1400/22/27 -Bx100 -By1 -BWSen -Ed -M1.5c -K -O -Y5c -T+r10 >> $PS
gmt pssac ntkl.z onkl.z -JX15c/4c -R200/1600/22/27 -Bx100 -By1 -BWSen -Ed -M1.5c -K -O -Y5c -T+s300 >> $PS
gmt pssac ntkl.z onkl.z -JX15c/4c -R-300/800/22/27 -Bx100 -By1 -BWSen -Ed -M1.5c -K -O -Y5c -T+t1+s100 >> $PS

gmt psxy -J$J -R$R -O -T >> $PS
rm gmt.*
