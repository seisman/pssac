## GMT5-pssac

This is pssac for GMT5.

- Works under GMT 5.2.1 only.
- Still under development. Do **NOT** use it now!
- Not compatible with old pssac or pssac2 syntax
- Compatible with GMT5 syntax (Hopefully)
- More features than old pssac or pssac2 (Hopefully)

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
gmt pssac
~~~

### Design of Options

Common Options defined by GMT:

- B: Specify frame and axes parameters
- J: Select map projection
- R: Specify region of interest
- P: Select portrait orientation
- U: Plot time-stamp on maps
- X: shift plot origin in x-direction
- Y: shift plot origin in y-direction
- K: Append more PS later
- O: This is an overlay plot
- V: verbose mode
- c: specify the number of copies
- t: layer transparency

- n: unused
- x: unused
- r: unused
- a: unused
- b: unused
- d: unused
- g: unused
- o: unused
- s: unused

- f
- h
- i
- p
- :

Options for pssac:

- D: offset traces, `-D<dx>/<dy>`
- W: pen attribution, `-W<pen>`
- G: positive/negative phase painting, `-G[p|n][+g<fill>][+z<zero>][+t<t0>/<t1>]`
- F: data preprocess before plotting, `-F[i|q|r]`
- E: determine profile type, `-Ea|b|k|d|n[<n>]`
- M: vertical scaling, `-M<size>[+a<alpha>]`

- A
- C
- H
- I
- L
- N
- Q
- S
- T
- Z

- e
- j
- k
- l
- m
- q
- u
- v
- w
- y
- z
