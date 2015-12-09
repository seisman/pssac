gmt set GMT_CUSTOM_LIBS=`pwd`/pssac.so
gmt pssac -R9/20/-2/2 -JX20c/10c -B1 -W2p,red seis.SAC > seismo.ps
