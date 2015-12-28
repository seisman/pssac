#define THIS_MODULE_NAME	"pssac"
#define THIS_MODULE_LIB		"sac"
#define THIS_MODULE_PURPOSE	"Plot seismograms in SAC format on maps"
#define THIS_MODULE_KEYS	"<DI,CCi,T-i,>XO,RG-"  // ???

#include "gmt_dev.h"
#include "sacio.h"

#define GMT_PROG_OPTIONS "-:>BJKOPRUVXYabcdfghipst" GMT_OPT("HMm")  // ???

struct PSSAC_CTRL {
	struct PSSAC_D {	/* -D<dx>/<dy> */
		bool active;
		double dx, dy;
	} D;
	struct PSSAC_W {	/* -W<pen> */
		bool active;
		struct GMT_PEN pen;
	} W;
};

enum Pssac_cliptype {
	PSSAC_CLIP_REPEAT 	= 0,
	PSSAC_CLIP_NO_REPEAT,
	PSSAC_NO_CLIP_REPEAT,
	PSSAC_NO_CLIP_NO_REPEAT};

void *New_pssac_Ctrl (struct GMT_CTRL *GMT) {	/* Allocate and initialize a new control structure */
	struct PSSAC_CTRL *C;

	C = GMT_memory (GMT, NULL, 1, struct PSSAC_CTRL);

	/* Initialize values whose defaults are not 0/false/NULL */
	C->W.pen = GMT->current.setting.map_default_pen;
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
	GMT_Message (API, GMT_TIME_NONE, "usage: pssac standardGMTOptions sacfiles [-W<pen>] [-D<dx>/<dy>]\n");
    GMT_Message (API, GMT_TIME_NONE, "\t-D offset traces by <dx>/<dy> [no offset].\n");
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
	int j;
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
			case 'W':		/* Set line attributes */
				Ctrl->W.active = true;
				if (opt->arg[0] && GMT_getpen (GMT, &opt->arg[0], &Ctrl->W.pen)) {
					GMT_pen_syntax (GMT, 'W', "sets pen attributes [Default pen is %s]:", 3);
					n_errors++;
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

#define bailout(code) {GMT_Free_Options (mode); return (code);}
#define Return(code) {Free_pssac_Ctrl (GMT, Ctrl); GMT_end_module (GMT, GMT_cpy); bailout (code);}

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

        data = read_sac(opt->arg, &hd);
	    GMT_Report (API, GMT_MSG_LONG_VERBOSE, "%s: xmin=%g xmax=%g ymin=%g ymax=%g\n", hd.b, hd.e, hd.depmin, hd.depmax);
        x = GMT_memory(GMT, 0, hd.npts, double);
        y = GMT_memory(GMT, 0, hd.npts, double);
        int i;
        for (i=0; i<hd.npts; i++) {
            x[i] = hd.b + i * hd.delta;
            y[i] = data[i];
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
