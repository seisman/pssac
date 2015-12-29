gmt set GMT_CUSTOM_LIBS=`pwd`/pssac.so
gmt pssac -R9/20/-2/2 -JX20c/10c -B1 -W2p,red seis.SAC > figure1.ps
gmt pssac -R9/20/-2/2 -JX20c/10c -B1 -W0p,black -G seis.SAC > figure2.ps
gmt pssac -R9/20/-2/2 -JX20c/10c -B1 -W0p,black -Gp+z0.2+t10/12+gblue seis.SAC > figure3.ps
gmt pssac -R9/20/-2/2 -JX20c/10c -B1 -W0p,black -Gp+z0+t10/12+gblue -Gn+z0+t12/15+gred seis.SAC > figure4.ps
gmt pssac -R9/20/-2/2 -JX20c/10c -B1 -W0p,black -Fqr seis.SAC > figure5.ps
