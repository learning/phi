#ifndef __PHI_BACKEND_VIEW__
#define __PHI_BACKEND_VIEW__

#include "types.h"
#include "file.h"
#include "selection.h"

typedef struct _phi_view
{
  uint id;
  phi_file *file;
  phi_selection *selection;
  struct _phi_view *next;
} phi_view;

/*
 * Function: phi_view_new
 * ----------------------
 *   Create a new view with specified file name
 *
 *   returns: phi_view pointer
 */
phi_view *phi_view_new(const char *filename);

/*
 * Function: phi_view_destroy
 * ----------------------
 *   Destroy the view and free memory
 */
void phi_view_destroy(phi_view *view);

#endif

