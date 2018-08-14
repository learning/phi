#ifndef __PHI_BACKEND_EXPLORER__
#define __PHI_BACKEND_EXPLORER__

#include "types.h"

typedef struct
{
} phi_explorer;

/*
 * Function: phi_explorer_new
 * ----------------------
 *   Create a new explorer
 *
 *   returns: phi_explorer pointer
 */
phi_explorer *phi_explorer_new(void);

/*
 * Function: phi_explorer_destroy
 * ----------------------
 *   Destroy the explorer and free memory
 */
void phi_explorer_destroy(phi_explorer *explorer);

#endif

