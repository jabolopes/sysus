#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char** argv) {
  int fd = open("hello.txt", O_RDONLY);
  if (fd == -1) {
    perror("failed to open file");
    return EXIT_FAILURE;
  }

  return 0;
}
