## PSSAC: Plot Seismograms in SAC format based on GMT

[![GitHub release](https://img.shields.io/github/release/seisman/pssac.svg)](https://github.com/seisman/pssac/releases)
[![license](https://img.shields.io/github/license/seisman/pssac.svg)](/LICENSE)

[pssac](https://github.com/seisman/pssac) is a [GMT](http://gmt.soest.hawaii.edu/) plugin,
which allows GMT users to plot seismograms in SAC format on maps.

pssac works for GMT 5.2.1 or above. It is based on original pssac code
developed by Prof. Lupei Zhu and pssac2 code by Prof. Brian Savage.
Note that, the pssac follows the standard GMT5 syntax, and
**NOT** compatible with old pssac or pssac2 syntax and usage.

### Installation

~~~bash
git clone https://github.com/seisman/pssac.git
cd pssac/
make
sudo cp pssac.so `gmt --show-plugindir`
~~~

### Usage

~~~bash
$ gmt pssac -
pssac(sac) 5.2.1 (r15220) [64-bit] [MP] - Plot seismograms in SAC format on maps

usage: pssac <saclist>|<sacfiles> -J<args> -R<west>/<east>/<south>/<north>[/<zmin>/<zmax>][r]
	[-B<args>] [-C[<t0>/<t1>]] [-D<dx>[/<dy>]] [-Ea|b|k|d|n[<n>]|u[<n>]] [-F[i][q][r]]
	[-G[p|n][+g<fill>][+t<t0>/<t1>][+z<zero>]] [-K] [-M<size>/<alpha>] [-O] [-P]
	[-T[+t<tmark>][+r<reduce_vel>][+s<shift>]] [-U[<just>/<dx>/<dy>/][c|<label>]] [-V[<level>]]
	[-W<pen>] [-X[a|c|r]<xshift>[<unit>]] [-Y[a|c|r]<yshift>[<unit>]] [-c<ncopies>]
	[-h[i|o][<nrecs>][+c][+d][+r<remark>][+t<title>]] [-t<+a|[-]n>] [-m<sec_per_measuer>] [-v]
~~~
