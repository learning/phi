#include <stdio.h>

#include "backend/file.h"

int main(int argc, const char *argv[]) {
  phi_file *file;

  if (argc > 1 && argv[1] != NULL) {
    // FILE *fp = fopen(argv[1], "r");
    // char str[100];

    // if (fp != NULL) {
    //   if (fgets(str, 100, fp) != NULL) {
    //     printf("str: %s\n", str);
    //   } else {
    //     printf("read failed.\n");
    //   }
    //   fclose(fp);
    // } else {
    //   printf("open failed.\n");
    // }

    file = phi_open_file(argv[1]);
    printf("\nfile id: %d\n", file->id);
    printf("file size: %zd\n", file->size);
    printf("allocated size: %zd\n", file->mem_size);
    printf("file content: %s\n\n", file->buffer);
    return phi_close_file(file);
  }
  printf("Please enter file name.\n");
  return 1;
}
