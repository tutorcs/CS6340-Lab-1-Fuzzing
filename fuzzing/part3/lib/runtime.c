https://tutorcs.com
WeChat: cstutorcs
QQ: 749389476
Email: tutorcs@163.com
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void __dbz_sanitizer__(int divisor, int line, int col) {
  if (divisor == 0) {
    printf("Divide-by-zero detected at line %d and col %d\n", line, col);
    exit(1);
  }
}

void __coverage__(int line, int col) {
  char exe[1024];
  int ret = readlink("/proc/self/exe", exe, sizeof(exe) - 1);
  if (ret == -1) {
    fprintf(stderr, "Error: Cannot find /projc/self/exe\n");
    exit(1);
  }
  exe[ret] = 0;

  char logfile[1024];
  int len = strlen(exe);
  strncpy(logfile, exe, len);
  logfile[len] = 0;
  strcat(logfile, ".cov");
  FILE *f = fopen(logfile, "a");
  fprintf(f, "%d,%d\n", line, col);
  fclose(f);
}
