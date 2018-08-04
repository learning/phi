#include "file.h"

unsigned int id = 1;

phi_file *opened_files = NULL;
phi_file *last_file = NULL;

phi_file *phi_open_file(const char *filename) {
	size_t result;
  phi_file *file = (phi_file *) malloc(sizeof(phi_file));

  file->handle = fopen(filename, "rw");
  if (file->handle == NULL) {
    fputs("File error", stderr);
    exit(1);
  }

  file->id = id++;
  file->dirty = false;
  file->encoding = UTF_8; // TODO: default encoding
  file->next = NULL;

  if (fseek(file->handle, 0, SEEK_END) != 0) {
    fputs("Seek error", stderr);
    exit(2);
  }
  file->size = ftell(file->handle);
  file->mem_size = (file->size / BUFFER_SIZE + 1) * BUFFER_SIZE; // Memory allocated
  file->buffer = (char *) malloc(file->mem_size);
  if (file->buffer == NULL) {
    fputs("Memory error", stderr);
    exit(3);
  }

  rewind(file->handle);
  result = fread(file->buffer, 1, file->size, file->handle);

  if (result != file->size) {
    fputs("Reading error", stderr);
    exit(4);
  }

  if (last_file == NULL) {
    // first opened file
    opened_files = file;
    last_file = file;
  } else {
    last_file->next = file;
    last_file = file;
  }
  return file;
}

int phi_close_file(phi_file *file) {
  int result;

  // remove from opened files
  phi_file *prev_file = opened_files;
  if (opened_files == file) {
    opened_files = file->next;
  } else {
    while (prev_file != NULL && prev_file->next != file) {
      prev_file = prev_file->next;
    }

    if (prev_file == NULL) {
      return 5;
    }

    prev_file->next = file->next;
  }

  // if file is last_file
  if (file == last_file) {
    last_file = prev_file;
  }

  // free buffer & close file handle
  free(file->buffer);
  result = fclose(file->handle);
  free(file);

  return result;
}
