#ifndef __PHI_APP__
#define __PHI_APP__

#include "../ptk/ptk.h"
#include "window.h"
#include "view.h"
#include "selection.h"
#include "region.h"
#include "buffer.h"

/*
 * Function: phi_init
 * ----------------------
 *   Phi initialize
 *
 *   param: platform specified parameter
 */
void phi_init(PlatformParam param);

/*
 * Function: phi_quit
 * ----------------------
 *   Quit phi app
 */
void phi_quit();

/*
 * Function: phi_load_state
 * ----------------------
 *   Load last phi state
 */
void phi_load_state();

/*
 * Function: phi_save_state
 * ----------------------
 *   Save current phi state for next launch
 */
void phi_save_state();

#endif
