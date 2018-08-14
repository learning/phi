#ifndef __PHI_BACKEND_FOLDER__
#define __PHI_BACKEND_FOLDER__

#include "types.h"

typedef struct _phi_folder
{
  char *path;
  struct _phi_folder *next;
} phi_folder;

/*
 * Function: phi_folder_new
 * ----------------------
 *   Create a new explorer
 *
 *   returns: phi_folder pointer
 */
phi_folder *phi_folder_new(const char *path);

/*
 * Function: phi_folder_destroy
 * ----------------------
 *   Destroy the explorer and free memory
 */
void phi_folder_destroy(phi_folder *explorer);

#endif

