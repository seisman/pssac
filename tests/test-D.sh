#!/bin/bash
R=9/20/-2/2
J=X15c/5c
B=1
PS=test-D.ps

gmt pssac -R$R -J$J -B$B seis.sac -K -P > $PS
gmt pssac -R$R -J$J -B$B seis.sac -Wred -K -O -D0.2c/0.2c >> $PS
gmt psxy -R$R -J$J -T -O >> $PS
rm gmt.*
