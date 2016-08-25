#!/bin/bash
J=M17c
R=-120/-50/40/65
Bx=x10
By=y5
PS=ex04.ps

gmt psxy -J$J -R$R -T -K > $PS
gmt pssac ../data/*.z -J$J -R$R -BWSen -B$Bx -B$By -M1i -m1000 -G+gblue -v -K -O >> $PS
saclst stlo stla f ../data/*.z | gmt psxy -J$J -R$R -Sc0.2c -Gred -i1,2 -K -O >> $PS
gmt psxy -J$J -R$R -T -O >> $PS
rm gmt.*
