#include <stdio.h>
#include "buffer.h"

PhiBuffer *phi_buffer_new(unsigned int size) {
  PhiBuffer *buffer = (PhiBuffer *) malloc(sizeof(PhiBuffer));
  unsigned int init_size;
  if (size % BUFFER_BLOCK == 0) {
    init_size = size;
  } else {
    init_size = size / BUFFER_BLOCK * BUFFER_BLOCK + BUFFER_BLOCK;
  }
  buffer->text = (char *) malloc(init_size);
  buffer->length = 0;
  buffer->mem_size = init_size;
  buffer->next = NULL;

  // Initialize the selections
  // phi_selection_add(buffer, 0, 0);
  return buffer;
}

void phi_buffer_destroy(PhiBuffer *buffer) {
  // phi_selection_clear(buffer);
  free(buffer);
}

void phi_buffer_insert(PhiBuffer *buffer, unsigned int pos, const char *text) {
  // Make sure insert position is valid.
  if (pos > buffer->length) pos = buffer->length;

  unsigned int length = strlen(text);

  // Make sure memory is enough after insert.
  unsigned int total_length = buffer->length + length;

  if (total_length >= buffer->mem_size) {
    // Allocate a new block of memories.
    unsigned int new_size =
      total_length / BUFFER_BLOCK * BUFFER_BLOCK + BUFFER_BLOCK;
    char *new_buf = (char *) malloc(new_size);
    memcpy(new_buf, buffer->text, buffer->length);
    free((void *) buffer->text);
    buffer->text = new_buf;
    buffer->mem_size = new_size;
  }

  // Memory is enough
  if (pos == buffer->length) {
    // Append
    memcpy(&buffer->text[buffer->length], text, length);
  } else {
    // Not append, insert at any position, use memmove
    memmove(&buffer->text[pos + length], &buffer->text[pos], buffer->length - pos);
    memcpy(&buffer->text[pos], text, length);
  }

  buffer->text[total_length] = '\0';
  buffer->length = total_length;
}

void phi_buffer_prepend(PhiBuffer *buffer, const char *text) {
  phi_buffer_insert(buffer, 0, text);
}

void phi_buffer_append(PhiBuffer *buffer, const char *text) {
  phi_buffer_insert(buffer, buffer->length, text);
}
