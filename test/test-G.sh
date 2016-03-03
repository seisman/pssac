#!/bin/bash
R=9/20/-2/2
J=X15c/6c
B=1
PS=test-G.ps

gmt pssac seis.sac -R$R -J$J -B$B -W0p -K -P -G > $PS
gmt pssac seis.sac -R$R -J$J -B$B -W0p -K -O -Y8c -G+gblue >> $PS
gmt pssac seis.sac -R$R -J$J -B$B -W0.1p -K -O -Y8c -Gp+z0.2+t10/13+gblue -Gn+z-0.2+t12/18+gred >> $PS

gmt psxy -R$R -J$J -O -T >> $PS
rm gmt.*
