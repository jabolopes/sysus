#define _GNU_SOURCE
#include <dlfcn.h>

#include <stdio.h>
#include <sys/types.h>

static struct {
  int init;
  int (*open)(const char * pathname, int flags, ...);
  int (*open64)(const char * pathname, int flags, ...);
} intercepts = {
  0,
  NULL,
  NULL,
};

static void init() {
  if (intercepts.init) {
    return;
  }

  intercepts.init = 1;
  intercepts.open = (int (*)(const char * pathname, int flags, ...))dlsym(RTLD_NEXT, "open");
  intercepts.open64 = (int (*)(const char * pathname, int flags, ...))dlsym(RTLD_NEXT, "open64");
}

int open(const char* pathname, int flags, mode_t mode) {
  fprintf(stderr, "intercept: open\n");
  init();

  return intercepts.open(pathname, flags, mode);
}

int open64(const char* pathname, int flags, mode_t mode) {
  fprintf(stderr, "intercept: open64\n");
  init();

  return intercepts.open64(pathname, flags, mode);
}
