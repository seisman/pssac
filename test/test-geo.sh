#!/bin/bash
J=M15c
R=-120/-40/30/70
Bx=x5
By=y5
PS=test-geo.ps

gmt pssac *.z -J$J -R$R -B$Bx -B$By -K -M1i -m600 > $PS
saclst stlo stla f *.z | gmt psxy -J$J -R$R -Sc0.5c -Gred -i1,2 -K -O >> $PS
gmt psxy -J$J -R$R -T -O >> $PS
rm gmt.*
