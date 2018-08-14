#include <stdio.h>

#include "../backend/backend.h"

int main(int argc, const char *argv[]) {
  phi_file *file1;
  phi_file *file2;
  phi_file *file3;

  if (argc > 1 && argv[1] != NULL) {
    printf("===============================\n");
    file1 = phi_file_open("test.xml");
    printf("file1 id: %d\n", file1->id);
    printf("file1 size: %zd\n", file1->size);
    printf("file1 allocated size: %zd\n", file1->mem_size);
    // printf("file1 content: %s\n\n", file1->buffer);

    printf("===============================\n");
    file2 = phi_file_open("test.bat");
    printf("file2 id: %d\n", file2->id);
    printf("file2 size: %zd\n", file2->size);
    printf("file2 allocated size: %zd\n", file2->mem_size);
    // printf("file2 content: %s\n\n", file2->buffer);

    printf("===============================\n");
    file3 = phi_file_open(argv[1]);
    printf("file3 id: %d\n", file3->id);
    printf("file3 size: %zd\n", file3->size);
    printf("file3 allocated size: %zd\n", file3->mem_size);

    file1->buffer[0] = 'h';
    file1->buffer[1] = 'e';
    file1->buffer[2] = 'l';
    file1->buffer[3] = 'l';
    file1->buffer[4] = 'o';
    // file1->buffer[5] = '\0';
    // file1->size = 5;
    phi_file_save(file1);
    // printf("file3 content: %s\n\n", file3->buffer);
    phi_file_close(file1);
    phi_file_close(file2);
    phi_file_close(file3);

    return 0;
  }
  printf("Please enter file name.\n");
  return 1;
}
