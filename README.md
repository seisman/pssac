## GMT5-pssac

This is pssac for GMT5.

- Works under GMT 5.2.1 only.
- Still under development, the usage may change.
- Not compatible with old pssac or pssac2 syntax
- Compatible with GMT5 syntax (Hopefully)
- More features than old pssac or pssac2 (Hopefully)
- Support Linux only. Will support Windows and Mac in the future

### How to compile

~~~bash
git clone https://github.com/seisman/GMT5-pssac.git
cd GMT5-pssac
# modify plugindir in Makefile
make
sudo make install
~~~

### Usage

~~~bash
$ gmt pssac -
pssac(sac) 5.2.1 (r15220) [64-bit] [MP] - Plot seismograms in SAC format on maps

usage: pssac [<saclist>| <sacfiles>] -J<args> -R<west>/<east>/<south>/<north>[/<zmin>/<zmax>][r]
	[-B<args>] [-C[<t0>/<t1>]] [-D<dx>[/<dy>]] [-Ea|b|k|d|n[<n>]|u[<n>]] [-F[i|q|r]]
	[-G[p|n][+g<fill>][+t<t0>/<t1>][+z<zero>]] [-K] [-M<size>/<alpha>] [-O] [-P]
	[-T+t<tmark>+r<reduce_vel>+s<shift>] [-U[<just>/<dx>/<dy>/][c|<label>]] [-V[<level>]]
	[-W<pen>] [-X[a|c|r]<xshift>[<unit>]] [-Y[a|c|r]<yshift>[<unit>]] [-c<ncopies>]
	[-h[i|o][<nrecs>][+c][+d][+r<remark>][+t<title>]] [-t<+a|[-]n>]
~~~

### Design of Options

GMT common options used by pssac:

- B: Specify frame and axes parameters
- J: Select map projection
- K: Append more PS later
- O: This is an overlay plot
- P: Select portrait orientation
- R: Specify region of interest
- U: Plot time-stamp on maps
- V: verbose mode
- X: shift plot origin in x-direction
- Y: shift plot origin in y-direction
- c: specify the number of copies
- h: input file have header records
- t: layer transparency

Possible useful GMT common options: `ip:`

Useless GMT common options: `abdfgonrsx`

Options used by pssac:

- C: cut data, `-C<t0>/<t1>`
- D: offset traces, `-D<dx>/<dy>`
- E: determine profile type, `-Ea|b|k|d|n[<n>]|u[n]`
- F: data preprocess before plotting, `-F[i|q|r]`
- G: positive/negative phase painting, `-G[p|n][+g<fill>][+z<zero>][+t<t0>/<t1>]`
- M: vertical scaling, `-M<size>[/<alpha>]`
- T: time alignment and shift. `-T+t<n>+r<reduce_vel>+s<shift>`
- W: pen attribution, `-W<pen>`
- m: time scaling while plotting on maps, `-m<sec_per_inch>`
- v: plot traces vertically

Options left for further use: `AHILNQSZejklquwyz`
