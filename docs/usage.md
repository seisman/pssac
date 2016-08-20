## GMT common options

- `-B`: Specify frame and axes parameters
- `-J`: Select map projection
- `-K`: Append more PS later
- `-O`: This is an overlay plot
- `-P`: Select portrait orientation
- `-R`: Specify region of interest
- `-U`: Plot time-stamp on maps
- `-V`: verbose mode
- `-X`: shift plot origin in x-direction
- `-Y`: shift plot origin in y-direction
- `-c`: specify the number of copies
- `-h`: input file have header records
- `-t`: layer transparency

## Options specific to pssac

### `-C[<t0>/<t1>]`

Cut data in timewindow between `<t0>` and `<t1>`.

`<t0>` and `<t1>` are relative to a reference time specified by `-T`. If `-T` option is not specified, use reference time in SAC header instead.

If only `-C` is used, `<t0>/<t1>` is determined as `xmin/xmax` from `-R` option.

### `-D<dx>[/<dy>]`

Offset seismogram locations by the given mount `<dx>/<dy>` [Default is no offset]. If `<dy>` is not given it is set equal to `<dx>`.

###  `-Ea|b|k|d|n[<n>]|u[<n>]`

Determine profile type (the type of Y axis).

- `a`: azimuth profile
- `b`: back-azimuth profile
- `k`: epicentral distance (in km) profile
- `d`: epicentral distance (in degree) profile
- `n`: traces are numbered from <n> to <n>+N in y-axis, default value of <n> is 0
- `u`: Y location is determined from SAC header user<n>, default using user0.

### `-F[i|q|r]`

Data preprocess before plotting.

- `i`: integral
- `q`: square
- `r`: remove mean value

`i|q|r` can repeat mutiple times, like -Frii will convert accerate to displacement. The order of i|q|r controls the order of the data processing.

### `-G[p|n][+g<fill>][+z<zero>][+t<t0>/<t1>]`

Paint positive or negative portion of traces.

If only `-G` is used, default to fill the positive portion black.

- `[p|n]` controls the painting of postive portion or negative portion. Repeat `-G` option to specify fills for different portion.
- `+g<fill>`: color to fill
- `+t<t0>/<t1>`: paint traces between t0 and t1 only. The reference time of t0 and t1 is determined by `-T` option.
- `+z<zero>`: define zero line. From `<zero>` to top is positive portion, from `<zero>` to bottom is negative portion.

### `-M<size>[u][/<alpha>]`

Vertical scaling.

- `<size>[u]`: each trace will scaled to `<size>[u]`. The default unit is PROJ_LENGTH_UNIT. The scale factor is defined as `yscale = size*(north-south)/(depmax-depmin)/map_height`
- `<size>/<alpha>`:
  - `<alpha>` < 0, use the same scale factor for all trace. The scale factor scale the first trace to `<size>[u]`
  - `<alpha>` = 0, yscale=size, no unit is allowed.
  - `<alpha>` > 0, yscale=size*r^alpha, r is the distance range in km.

### `-T+t<n>+r<reduce_vel>+s<shift>`

Time alignment and shift.

- `+t<tmark>`: align all trace along time mark. <tmark> are -5(b), -3(o), -2(a), 0-9(t0-t9).
- `+r<reduce_vel>`: reduce velocity in km/s.
- `+s<shift>`: shift all traces by <shift> seconds

### `-W<pen>`

Set pen attribution [Default pen is default,black].

### `-m<sec_per_inch>`

Time scaling while plotting on maps.

### `-v`

Plot traces vertically.
