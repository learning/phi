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
 * Function: phi_file_open
 * ----------------------
 *   Open a file
 *
 *   returns: phi_file pointer
 */
phi_file *phi_file_open(const char *filename);

/*
 * Function: phi_file_close
 * ----------------------
 *   Close a file
 *
 *   returns: zero for success, and non-zero for error code
 */
int phi_file_close(phi_file *file);

/*
 * Function: phi_file_save
 * ----------------------
 *   Save file
 *
 *   returns: zero for success, and non-zero for error code
 */
int phi_file_save(phi_file *file);

/*
 * Function: phi_file_reopen
 * ----------------------
 *   Reopen file, when it's modified elsewhere
 *
 *   returns: zero for success, and non-zero for error code
 */
int phi_file_reopen(phi_file *file);

#endif

