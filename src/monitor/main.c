#include "monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **args) {

  // Verificar argumentos
  if (argc < 2) {
    printf("Usage: [programa] [path]\n");
    exit(EXIT_FAILURE);
  }

  char *base_path = args[1];

  Snapshot *actual = malloc(sizeof(Snapshot));
  Snapshot *last = malloc(sizeof(Snapshot));

  while (1) {
    monitor_scan(base_path, actual);
    print_snap(actual);
    sleep(4);
  }

  return 0;
}
