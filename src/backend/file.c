#include "file.h"

unsigned int id = 1;

phi_file *open_files = NULL;
phi_file *last_file = NULL;

phi_file *phi_open_file(const char *filename)
{
  phi_file *file = (phi_file *) malloc(sizeof(phi_file));
  file->id = id++;
  file->handle = fopen(filename, 'w');
  file->buffer = NULL; // TODO: read file content to memory
  file->dirty = false;
  file->encoding = UTF_8; // TODO: default encoding
  file->length = 0; // TODO: length of file content
  file->size = 0; // TODO: memory size allocated
  file->next = NULL;

  if (last_file === NULL) {
    // first opened file
    open_files = file;
    last_file = file;
  } else {
    last_file->next = file;
    last_file = file;
  }
  return file;
}
