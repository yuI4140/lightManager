#include "../headers/defines.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PERCENTAGE 0.03
i32 getCmd(const char *command, void **ret) {
  FILE *f;
  char buffer[256];
  f = popen(command, "r");
  while (fgets(buffer, sizeof(buffer), f) != NULL) {
    buffer[strcspn(buffer, "\n")] = '\0';
    *ret = strdup(buffer);
  }
  pclose(f);
  if (*ret != NULL) {
    return true;
  }
  return false;
}
char *initCharp() {
  char *ret = (char *)malloc(256);
  ret[0] = '\0';
  return ret;
}
int main(i32 argc, char **argv) {
  void *back = NULL;
  if (argc < 2) {
    printf("usage: %s %s\n", argv[0], "[inc|dec]");
    exit(0);
  }
  if (getCmd("brightnessctl get", &back)) {
    char *light = (char *)back;
    i32 i_light = atoi(light);
    if (strcmp(argv[1], "inc") == 0) {
      i32 inc = i_light + (i32)(i_light * PERCENTAGE);
      char *buffer = initCharp();
      sprintf(buffer, "brightnessctl set %d", inc);
      system(buffer);
      free(buffer);
    }
    if (strcmp(argv[1], "dec") == 0) {
      i32 dec = i_light - (i32)(i_light * PERCENTAGE);
      char *buffer = initCharp();
      sprintf(buffer, "brightnessctl set %d", dec);
      system(buffer);
      free(buffer);
    }
    free(back);
  }
  return 0;
}
