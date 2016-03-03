#!/bin/bash
J=X15c/5c
R=9/20/-2/2
Bx=x2
By=y1
PS=test-common-options.ps

gmt pssac -J$J -R$R -B$Bx -B$By -B+t"Option -P for portrait mode" -K -P seis.sac > $PS
gmt pssac -J$J -R$R -B$Bx -B$By -B+t"Option -X and -Y" -Y10c -Xa1c -K -O seis.sac >> $PS
gmt pssac -J$J -R$R -B$Bx -B$By -B+t"Option -U and -t" -Y10c -K -O -Uc -t50 seis.sac >> $PS

gmt psxy -J$J -R$R -T -O >> $PS
rm gmt.*
