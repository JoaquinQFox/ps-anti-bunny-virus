#include "detector/detector.h"
#include "monitor/monitor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_SUSPICUOUS 10

int main(int argc, char **args) {

  // Verificar argumentos
  if (argc < 2) {
    printf("Usage: [programa] [path]\n");
    exit(EXIT_FAILURE);
  }

  char *base_path = args[1];

  Snapshot *actual = malloc(sizeof(Snapshot));
  Snapshot *last = malloc(sizeof(Snapshot));

  memset(actual, 0, sizeof(Snapshot));
  memset(last, 0, sizeof(Snapshot));

  Suspicious sospechosos[MAX_SUSPICUOUS];
  while (1) {
    // Hace un escaneo de los arhivos y actualiza en snapshot actual
    monitor_scan(base_path, actual);

    int n_sospechosos =
        detect_suspicious(last, actual, 1000, sospechosos, MAX_SUSPICUOUS);

    if (n_sospechosos > 0) {
      printf("Sospechosos encontrados: %d\n", n_sospechosos);
      for (int i = 0; i < n_sospechosos; i++) {
        printf(" - %s (%.2f bytes/seg, tamano actual: %ld)\n",
               sospechosos[i].path, sospechosos[i].bytes_rate,
               (long)sospechosos[i].actual_size);
      }
    }

    // Intercambia punteros para no crear mas
    Snapshot *temp = last;
    last = actual;
    actual = temp;

    usleep(500);
  }

  return 0;
}
