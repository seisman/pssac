#!/bin/bash
J=M12c
R=-120/-40/30/70
Bx=x10
By=y5
PS=test-geo.ps

gmt psxy -J$J -R$R -T -K > $PS
# left
gmt pssac *.z -J$J -R$R -BWSen -B$Bx -B$By -M0.5i -m800 -K -O >> $PS
saclst stlo stla f *.z | gmt psxy -J$J -R$R -Sc0.5c -Gred -i1,2 -K -O >> $PS

# right
gmt pssac *.z -J$J -R$R -BWSen -B$Bx -B$By -M0.5i -m800 -v -K -O -X14c >> $PS
saclst stlo stla f *.z | gmt psxy -J$J -R$R -Sc0.5c -Gred -i1,2 -K -O >> $PS

gmt psxy -J$J -R$R -T -O >> $PS
rm gmt.*
