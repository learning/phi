#ifndef __PHI_FILE__
#define __PHI_FILE__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define BUFFER_SIZE 102400 // 100kb

typedef enum
{
  UTF_8,
  NUMBER_OF_ENCODINGS
} phi_encoding;

typedef struct _phi_file
{
  unsigned int id;
  FILE *handle;
  char *buffer;
  bool dirty;
  phi_encoding encoding;
  size_t size;
  size_t mem_size;
  struct _phi_file *next;
} phi_file;

/*
 * Function: phi_open_file
 * ----------------------
 *   Open a file
 *
 *   returns:
 */
phi_file *phi_open_file(const char *filename);

int phi_close_file(phi_file *file);


#endif

