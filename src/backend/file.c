#include "file.h"

uint file_id = 1;

phi_file *opened_files = NULL;
phi_file *last_file = NULL;

phi_file *phi_file_open(const char *filename) {
  size_t result;
  phi_file *file;
  FILE *handle;
  size_t filename_length;

  // Empty buffer, without a filename
  if (filename == NULL) {
    file = (phi_file *) malloc(sizeof(phi_file));
    file->id = file_id++;
    file->filename = NULL;
    file->dirty = false;
    file->encoding = UTF_8;
    file->size = 0;
    file->mem_size = BUFFER_SIZE;
    file->refs = 1;
    file->next = NULL;
    file->buffer = (char *) malloc(file->mem_size);
    file->buffer[0] = '\0';
  } else {
    filename_length = strlen(filename);

    // find in opened_files by filename
    file = opened_files;
    while (file != NULL) {
      if (strlen(file->filename) == filename_length &&
          memcmp(file->filename, filename, filename_length) == 0) {
        // the same file, add reference count and return
        ++file->refs;
        return file;
      }
      file = file->next;
    }

    file = (phi_file *) malloc(sizeof(phi_file));

    handle = fopen(filename, "r");
    if (handle == NULL) {
      fputs("[phi_file_open] File error", stderr);
      return NULL;
    }

    file->id = file_id++;
    file->filename = (char *) malloc(filename_length + 1);
    memcpy(file->filename, filename, filename_length + 1);

    file->dirty = false;
    file->encoding = UTF_8; // TODO: default encoding
    file->next = NULL;
    file->refs = 1;

    if (fseek(handle, 0, SEEK_END) != 0) {
      fputs("[phi_file_open] Seek error", stderr);
      return NULL;
    }
    file->size = ftell(handle);
    file->mem_size = (file->size / BUFFER_SIZE + 1) * BUFFER_SIZE; // Memory allocated
    file->buffer = (char *) malloc(file->mem_size);
    if (file->buffer == NULL) {
      fputs("[phi_file_open] Memory error", stderr);
      return NULL;
    }

    rewind(handle);
    result = fread(file->buffer, 1, file->size, handle);

    if (result != file->size) {
      fputs("[phi_file_open] Reading error", stderr);
      return NULL;
    }

    fclose(handle);
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

int phi_file_close(phi_file *file) {
  int result;

  if (file->refs > 1) {
    --file->refs;
    return 0;
  }

  // the last reference call
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
  free(file);

  return result;
}

int phi_file_save(phi_file *file) {
  FILE *handle = fopen(file->filename, "w");
  size_t result = fwrite(file->buffer, 1, file->size, handle);
  fclose(handle);

  if (result == file->size) {
    file->dirty = false;
    return 0;
  }
  return 1;
}

int phi_file_reopen(phi_file *file) {
  size_t mem_size;
  size_t result;
  FILE *handle = fopen(file->filename, "r");

  if (handle == NULL) {
    fputs("[phi_file_reopen] File error", stderr);
    return 1;
  }

  if (fseek(handle, 0, SEEK_END) != 0) {
    fputs("[phi_file_reopen] Seek error", stderr);
    return 2;
  }

  file->size = ftell(handle);
  mem_size = (file->size / BUFFER_SIZE + 1) * BUFFER_SIZE; // new memory size

  if (mem_size > file->mem_size) {
    // new memory size greater than current memory size
    // need to allocate a bigger memory block
    file->mem_size = mem_size;
    free(file->buffer);
    file->buffer = (char *) malloc(file->mem_size);
    if (file->buffer == NULL) {
      fputs("[phi_file_reopen] Memory error", stderr);
      return 3;
    }
  }

  rewind(handle);
  result = fread(file->buffer, 1, file->size, handle);

  if (result != file->size) {
    fputs("[phi_file_reopen] Reading error", stderr);
    return 4;
  }

  fclose(handle);
  return 0;
}
