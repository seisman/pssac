#define THIS_MODULE_NAME	"pssac"
#define THIS_MODULE_LIB		"sac"
#define THIS_MODULE_PURPOSE	"Plot seismograms in SAC format on maps"
#define THIS_MODULE_KEYS	"<DI,CCi,T-i,>XO,RG-"  // ???

#include "gmt_dev.h"
#include "sacio.h"

#define GMT_PROG_OPTIONS "->BJRPUXYKOVct"

struct PSSAC_CTRL {
	struct PSSAC_D {	/* -D<dx>/<dy> */
		bool active;
		double dx, dy;
	} D;
	struct PSSAC_W {	/* -W<pen> */
		bool active;
		struct GMT_PEN pen;
	} W;
    struct PSSAC_G {  /* -G[p|n]+g<fill>+z<zero>+t<t0>/<t1> */
        bool active[2];
        struct GMT_FILL fill[2];
        float zero[2];
        bool cut[2];
        float t0[2];
        float t1[2];
    } G;
    struct PSSAC_F { /* -Fiqr */
        bool active;
        char keys[GMT_LEN256];
    } F;
    struct PSSAC_E { /* -Ea|b|d|k|n<n> */
        bool active;
        char keys[2];
    } E;
};

void *New_pssac_Ctrl (struct GMT_CTRL *GMT) {	/* Allocate and initialize a new control structure */
	struct PSSAC_CTRL *C;

	C = GMT_memory (GMT, NULL, 1, struct PSSAC_CTRL);

	/* Initialize values whose defaults are not 0/false/NULL */
	C->W.pen = GMT->current.setting.map_default_pen;

    C->G.zero[0] = C->G.zero[1] = 0.0;
    GMT_init_fill (GMT, &C->G.fill[0], 0.0, 0.0, 0.0);  /* default fill black */
    C->G.fill[1] = C->G.fill[0];
	return (C);
}

void Free_pssac_Ctrl (struct GMT_CTRL *GMT, struct PSSAC_CTRL *C) {	/* Deallocate control structure */
	if (!C) return;
	GMT_freepen (GMT, &C->W.pen);
	GMT_free (GMT, C);
}

int GMT_pssac_usage (struct GMTAPI_CTRL *API, int level)
{
	/* This displays the pssac synopsis and optionally full usage information */

	GMT_show_name_and_purpose (API, THIS_MODULE_LIB, THIS_MODULE_NAME, THIS_MODULE_PURPOSE);
	if (level == GMT_MODULE_PURPOSE) return (GMT_NOERROR);
	GMT_Message (API, GMT_TIME_NONE, "usage: pssac standardGMTOptions sacfiles [-W<pen>] [-D<dx>/<dy>] [-F[i|q|r]]\n");
	GMT_Message (API, GMT_TIME_NONE, "\t-G[p|n][+g<fill>][+t<t0>/<t1>][+z<zero>] [-Ea|b|k|d|n<n>]\n");
    GMT_Message (API, GMT_TIME_NONE, "\n");
    GMT_Message (API, GMT_TIME_NONE, "\t-D offset traces by <dx>/<dy> [no offset].\n");
    GMT_Message (API, GMT_TIME_NONE, "\t-E profile type. \n");
    GMT_Message (API, GMT_TIME_NONE, "\t   a: azimuth profile\n");
    GMT_Message (API, GMT_TIME_NONE, "\t   b: back-azimuth profile\n");
    GMT_Message (API, GMT_TIME_NONE, "\t   k: epicentral distance (in km) profile\n");
    GMT_Message (API, GMT_TIME_NONE, "\t   d: epicentral distance (in degree) profile \n");
    GMT_Message (API, GMT_TIME_NONE, "\t   n: traces are numbered from <n> to <n>+N in y-axis, default value of <n> is 0\n");
    GMT_Message (API, GMT_TIME_NONE, "\t-F data preprocess before plotting.\n");
    GMT_Message (API, GMT_TIME_NONE, "\t   [i|q|r] can repeat mutiple times, the data processing is determined by the order of the options.\n");
    GMT_Message (API, GMT_TIME_NONE, "\t   i: integral.\n");
    GMT_Message (API, GMT_TIME_NONE, "\t   q: square.\n");
    GMT_Message (API, GMT_TIME_NONE, "\t   r: remove mean value.\n");
    GMT_pen_syntax (API->GMT, 'W', "Set pen attributes [Default pen is %s]:", 0);

	if (level == GMT_SYNOPSIS) return (EXIT_FAILURE);

	return (EXIT_FAILURE);
}

int GMT_pssac_parse (struct GMT_CTRL *GMT, struct PSSAC_CTRL *Ctrl, struct GMT_OPTION *options)
{
	/* This parses the options provided to pssac and sets parameters in Ctrl.
	 * Note Ctrl has already been initialized and non-zero default values set.
	 * Any GMT common options will override values set previously by other commands.
	 * It also replaces any file names specified as input or output with the data ID
	 * returned when registering these sources/destinations with the API.
	 */

	unsigned int n_errors = 0;
	int j, k;
	char txt_a[GMT_LEN256] = {""}, txt_b[GMT_LEN256] = {""};
	struct GMT_OPTION *opt = NULL;
	struct GMTAPI_CTRL *API = GMT->parent;

	for (opt = options; opt; opt = opt->next) {	/* Process all the options given */

		switch (opt->option) {

			case '<':	/* Skip input files */
				if (!GMT_check_filearg (GMT, '<', opt->arg, GMT_IN, GMT_IS_DATASET)) n_errors++;
				break;

			/* Processes program-specific parameters */

			case 'D':
				if ((j = sscanf (opt->arg, "%[^/]/%s", txt_a, txt_b)) < 1) {
					GMT_Report (API, GMT_MSG_NORMAL, "Syntax error -D option: Give x [and y] offsets\n");
					n_errors++;
				}
				else {
					Ctrl->D.dx = GMT_to_inch (GMT, txt_a);
					Ctrl->D.dy = (j == 2) ? GMT_to_inch (GMT, txt_b) : Ctrl->D.dx;
					Ctrl->D.active = true;
				}
				break;

            case 'E':
                Ctrl->E.active = true;
                strcpy(Ctrl->E.keys, &opt->arg[0]);
                break;

            case 'F':
                Ctrl->F.active = true;
                strcpy(Ctrl->F.keys, &opt->arg[0]);
                break;
			case 'W':		/* Set line attributes */
				Ctrl->W.active = true;
				if (opt->arg[0] && GMT_getpen (GMT, &opt->arg[0], &Ctrl->W.pen)) {
					GMT_pen_syntax (GMT, 'W', "sets pen attributes [Default pen is %s]:", 3);
					n_errors++;
				}
				break;
            case 'G':      /* phase painting */
                switch (opt->arg[0]) {
                    case 'p': j = 1, k = 0; break;
                    case 'n': j = 1, k = 1; break;
                    default : j = 0, k = 0; break;
                }
                Ctrl->G.active[k] = true;
                unsigned int pos;
                char p[GMT_BUFSIZ] = {""};
                pos = j;
                while (GMT_getmodopt (GMT, opt->arg, "gtz", &pos, p)) {
                    switch (p[0]) {
                        case 'g':  /* fill */
                            if (GMT_getfill (GMT, &p[1], &Ctrl->G.fill[k])) {
                                GMT_Report (API, GMT_MSG_NORMAL, "Syntax error -G+g<fill> option.\n");
                                n_errors++;
                            }
                            break;
                        case 'z':  /* zero */
                            Ctrl->G.zero[k] = atof (&p[1]);
                            break;
                        case 't':  /* +t<t0>/<t1> */
                            Ctrl->G.cut[k] = true;
                            if (sscanf (&p[1], "%f/%f", &Ctrl->G.t0[k], &Ctrl->G.t1[k]) != 2) {
                                GMT_Report (API, GMT_MSG_NORMAL, "Syntax error -G+t<t0>/<t1> option.\n");
                                n_errors++;
                            }
                            break;
                        default:
                            GMT_Report (API, GMT_MSG_NORMAL, "Syntax error\n");
                            break;
                    }
                }
                break;
			default:	/* Report bad options */
				n_errors += GMT_default_error (GMT, opt->option);
				break;
		}
	}

	/* Check that the options selected are mutually consistent */

	n_errors += GMT_check_condition (GMT, !GMT->common.R.active, "Syntax error: Must specify -R option\n");
	n_errors += GMT_check_condition (GMT, !GMT->common.J.active, "Syntax error: Must specify a map projection with the -J option\n");

	return (n_errors ? GMT_PARSE_ERROR : GMT_OK);
}

double linear_interpolate_x (double x0, double y0, double x1, double y1, double y) {
    return (x1-x0)/(y1-y0)*(y-y0) + x0;
}
double linear_interpolate_y (double x0, double y0, double x1, double y1, double x) {
    return (y1-y0)/(x1-x0)*(x-x0) + y0;
}

#define bailout(code) {GMT_Free_Options (mode); return (code);}
#define Return(code) {Free_pssac_Ctrl (GMT, Ctrl); GMT_end_module (GMT, GMT_cpy); bailout (code);}

void paint_phase(struct GMT_CTRL *GMT, struct PSSAC_CTRL *Ctrl, struct PSL_CTRL *PSL, double *x, double *y, int n, int mode)
{
    /* mode=0: paint positive phase */
    /* mode=1: paint negative phase */
    int i, ii;
    double *xx = NULL, *yy = NULL;
    double zero = Ctrl->G.zero[mode];
    double t0 = Ctrl->G.t0[mode];
    double t1 = Ctrl->G.t1[mode];

    xx = GMT_memory (GMT, 0, n+2, double);
    yy = GMT_memory (GMT, 0, n+2, double);

    for (i=0; i<n; i++) {
        if ((x[i]>t0) && ((mode==0 && y[i]>zero) || (mode==1 && y[i]<zero))) {
            ii = 0;
            /* first point of polygon */
            yy[ii] = zero;
            if (i==0)
                xx[ii] = x[i];
            else
                xx[ii] = linear_interpolate_x(x[i-1], y[i-1], x[i], y[i], yy[ii]);
            ii++;

            while((i<n) && (x[i]<t1) && ((mode==0 && y[i]>zero) || (mode==1 && y[i]<zero))) {
                xx[ii] = x[i];
                yy[ii] = y[i];
                i++;
                ii++;
            }

            /* last point of polygon */
            yy[ii] = zero;
            if (i==n)
                xx[ii] = x[i-1];
            else
                xx[ii] = linear_interpolate_x(x[i-1], y[i-1], x[i], y[i], yy[ii]);
            ii++;

            if ((GMT->current.plot.n = GMT_geo_to_xy_line(GMT, xx, yy, ii)) < 3) continue;
            GMT_setfill(GMT, &Ctrl->G.fill[mode], false);
            PSL_plotpolygon(PSL, GMT->current.plot.x, GMT->current.plot.y, GMT->current.plot.n);
        }
    }
}

void integral (double *y, double delta, int n)
{
    int i;
    y[0] = (y[0]+y[1])*delta/2.0;

    for (i=1; i<n-1; i++)
        y[i] = y[i-1] + (y[i] + y[i+1]) * delta / 2.0;
}

void rmean (double *y, int n)
{
    int i;
    double depmen = 0.0;
    for (i=0; i<n; i++) depmen += y[i];
    depmen /= n;

    for (i=0; i<n; i++) y[i] -= depmen;
}

void sqr (double *y, int n) {
    int i;
    for (i=0; i<n; i++) y[i] *= y[i];
}

int GMT_pssac (void *V_API, int mode, void *args)
{	/* High-level function that implements the pssac task */
	bool old_is_world;
	int error = GMT_NOERROR;

	struct GMT_PEN current_pen;
	struct PSSAC_CTRL *Ctrl = NULL;
	struct GMT_CTRL *GMT = NULL, *GMT_cpy = NULL;		/* General GMT interal parameters */
	struct GMT_OPTION *options = NULL;
	struct PSL_CTRL *PSL = NULL;		/* General PSL interal parameters */
	struct GMTAPI_CTRL *API = GMT_get_API_ptr (V_API);	/* Cast from void to GMTAPI_CTRL pointer */


	/*----------------------- Standard module initialization and parsing ----------------------*/

	if (API == NULL) return (GMT_NOT_A_SESSION);
	if (mode == GMT_MODULE_PURPOSE) return (GMT_pssac_usage (API, GMT_MODULE_PURPOSE));	/* Return the purpose of program */
	options = GMT_Create_Options (API, mode, args);	if (API->error) return (API->error);	/* Set or get option list */

	if (!options || options->option == GMT_OPT_USAGE) bailout (GMT_pssac_usage (API, GMT_USAGE));	/* Return the usage message */
	if (options->option == GMT_OPT_SYNOPSIS) bailout (GMT_pssac_usage (API, GMT_SYNOPSIS));	/* Return the synopsis */

	/* Parse the command-line arguments; return if errors are encountered */

	GMT = GMT_begin_module (API, THIS_MODULE_LIB, THIS_MODULE_NAME, &GMT_cpy); /* Save current state */
	if (GMT_Parse_Common (API, GMT_PROG_OPTIONS, options)) Return (API->error);

	Ctrl = New_pssac_Ctrl (GMT);	/* Allocate and initialize a new control structure */
	if ((error = GMT_pssac_parse (GMT, Ctrl, options)) != 0) Return (error);

	/*---------------------------- This is the pssac main code ----------------------------*/

	GMT_Report (API, GMT_MSG_VERBOSE, "Processing input SAC files\n");
	current_pen = Ctrl->W.pen;

	if (GMT_err_pass (GMT, GMT_map_setup (GMT, GMT->common.R.wesn), "")) Return (GMT_PROJECTION_ERROR);

	if ((PSL = GMT_plotinit (GMT, options)) == NULL) Return (GMT_RUNTIME_ERROR);

	GMT_plane_perspective (GMT, GMT->current.proj.z_project.view_plane, GMT->current.proj.z_level);
	GMT_plotcanvas (GMT);	/* Fill canvas if requested */

	GMT_setpen (GMT, &current_pen);

	if (Ctrl->D.active) PSL_setorigin (PSL, Ctrl->D.dx, Ctrl->D.dy, 0.0, PSL_FWD);	/* Shift plot a bit */

	old_is_world = GMT->current.map.is_world;

	struct GMT_OPTION *opt = NULL;
    int n_files = 0;
	for (opt = options; opt; opt = opt->next) {	/* Process all the options given */
        if (opt->option != '<') continue;  /* skip options */
        n_files++;

	    GMT_Report (API, GMT_MSG_LONG_VERBOSE, "Reading SAC file %d: %s\n", n_files, opt->arg);
        SACHEAD hd;
        float *data = NULL;
        double *x = NULL, *y = NULL;
        double y0;

        data = read_sac(opt->arg, &hd);
	    GMT_Report (API, GMT_MSG_LONG_VERBOSE, "%s: xmin=%g xmax=%g ymin=%g ymax=%g\n", hd.b, hd.e, hd.depmin, hd.depmax);
        x = GMT_memory(GMT, 0, hd.npts, double);
        y = GMT_memory(GMT, 0, hd.npts, double);
        int i;
        for (i=0; i<hd.npts; i++) {
            x[i] = hd.b + i * hd.delta;
            y[i] = data[i];
        }

        /* deal with -F option */
        for (i=0; Ctrl->F.keys[i]!='\0'; i++) {
            switch (Ctrl->F.keys[i]) {
                case 'i': integral(y, hd.delta, hd.npts); hd.npts--; break;
                case 'q':   sqr(y, hd.npts); break;
                case 'r': rmean(y, hd.npts); break;
                default: break;
            }
        }

        /* profile */
        if (Ctrl->E.active) {
            switch (Ctrl->E.keys[0]) {
                case 'a': y0 = hd.az; break;
                case 'b': y0 = hd.baz; break;
                case 'd': y0 = hd.gcarc; break;
                case 'k': y0 = hd.dist; break;
                case 'n':
                    y0 = n_files - 1;
                    if (Ctrl->E.keys[1]!='\0')
                        y0 += atof(&Ctrl->E.keys[1]);
                    break;
            }
        }

        for (i=0; i<hd.npts; i++) {
            y[i] += y0;
        }

        for (i=0; i<=1; i++) { /* 0=positive; 1=negative */
            if (Ctrl->G.active[i]) {
                if (!Ctrl->G.cut[i]) {
                    Ctrl->G.t0[i] = x[0];
                    Ctrl->G.t1[i] = x[hd.npts-1];
                }
                paint_phase(GMT, Ctrl, PSL, x, y, hd.npts, i);
            }
        }
        GMT->current.plot.n = GMT_geo_to_xy_line (GMT, x, y, hd.npts);
        GMT_plot_line (GMT, GMT->current.plot.x, GMT->current.plot.y, GMT->current.plot.pen, GMT->current.plot.n, current_pen.mode);

        GMT_free(GMT, x);
        GMT_free(GMT, y);
        GMT_free(GMT, data);
    }

	if (Ctrl->D.active) PSL_setorigin (PSL, -Ctrl->D.dx, -Ctrl->D.dy, 0.0, PSL_FWD);	/* Reset shift */

	PSL_setdash (PSL, NULL, 0);
	GMT->current.map.is_world = old_is_world;

	GMT_map_basemap (GMT);
	GMT_plane_perspective (GMT, -1, 0.0);

	GMT_plotend (GMT);

	Return (GMT_OK);
}
