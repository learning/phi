#ifndef __PHI_BUFFER__
#define __PHI_BUFFER__

#include <stdlib.h>
#include <string.h>

/* default extend block is 4k */
#define BUFFER_BLOCK 4096

/* A text buffer for phi, every editor/file has one buffer. */
typedef struct phi_buffer_t {
  char *text;          // The actual buffer to store text
  unsigned int length; // Total text length
  unsigned int mem_size; // Buffer memory size
  struct phi_buffer_t *next;
} PhiBuffer;

PhiBuffer *phi_buffer_new(unsigned int size);
void phi_buffer_destroy(PhiBuffer *buffer);
void phi_buffer_insert(PhiBuffer *buffer, unsigned int pos, const char *text);
void phi_buffer_prepend(PhiBuffer *buffer, const char *text);
void phi_buffer_append(PhiBuffer *buffer, const char *text);

#endif
