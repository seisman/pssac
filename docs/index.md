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
