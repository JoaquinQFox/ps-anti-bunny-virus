#define _XOPEN_SOURCE 500

#include <sys/stat.h>
#include "monitor.h"
#include <ftw.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

static int callback_archivo(const char *ruta, const struct stat *info, int tipo, struct FTW *ftwbuf) {
    // Si no es archivo no se analiza
    if (tipo != FTW_F) {
        return 0;
    }

    printf("Path = %s\n", ruta);
    return 0;
}

int monitor_scan(const char *base_path, Snapshot *snap) {
  memset(snap, 0, sizeof(Snapshot));
  snap->timestamp = time(NULL);

  // Recorre cada archivo y realiza funcion
  nftw(base_path, callback_archivo, 50, FTW_PHYS);

  return 0;
}
