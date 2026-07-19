#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "detector.h"

int main() {
    Snapshot* anterior = malloc(sizeof(Snapshot));
    Snapshot* actual = malloc(sizeof(Snapshot));

    memset(anterior, 0, sizeof(Snapshot));
    memset(actual, 0, sizeof(Snapshot));

    anterior->timestamp = 1000;
    actual->timestamp = 1001;   // 1 segundo despues

    // Simular un archivo que crecio MUCHO en 1 segundo
    strcpy(anterior->files[0].path, "/tmp/prueba.bin");
    anterior->files[0].size = 100;
    anterior->cantidad = 1;

    strcpy(actual->files[0].path, "/tmp/prueba.bin");
    actual->files[0].size = 2000000;   // crecio de 100 a 2,000,000 bytes en 1 seg
    actual->cantidad = 1;

    Suspicious sospechosos[10];
    int n = detect_suspicious(anterior, actual, 500000, sospechosos, 10);

    printf("Sospechosos encontrados: %d\n", n);
    for (int i = 0; i < n; i++) {
        printf(" - %s (%.2f bytes/seg, tamano actual: %ld)\n",
               sospechosos[i].path,
               sospechosos[i].bytes_rate,
               (long)sospechosos[i].actual_size);
    }

    return 0;
}
