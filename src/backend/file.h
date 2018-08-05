#ifndef __PHI_FILE__
#define __PHI_FILE__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define BUFFER_SIZE 512 // 512 bytes

typedef enum
{
  UTF_8,
  NUMBER_OF_ENCODINGS
} phi_encoding;

typedef struct _phi_file
{
  unsigned int id;
  char *filename;
  char *buffer;
  bool dirty;
  phi_encoding encoding;
  size_t size;
  size_t mem_size;
  unsigned int refs; // reference count
  struct _phi_file *next;
} phi_file;

/*
 * Function: phi_open_file
 * ----------------------
 *   Open a file
 *
 *   returns: phi_file pointer
 */
phi_file *phi_open_file(const char *filename);

/*
 * Function: phi_close_file
 * ----------------------
 *   Close a file
 *
 *   returns: zero for success, and non-zero for error code
 */
int phi_close_file(phi_file *file);

/*
 * Function: phi_save_file
 * ----------------------
 *   Save file
 *
 *   returns: zero for success, and non-zero for error code
 */
int phi_save_file(phi_file *file);

/*
 * Function: phi_reopen_file
 * ----------------------
 *   Reopen file, when it's modified elsewhere
 *
 *   returns: zero for success, and non-zero for error code
 */
int phi_reopen_file(phi_file *file);

#endif

