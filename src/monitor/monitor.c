#define _XOPEN_SOURCE 500

#include <sys/stat.h>
#include "monitor.h"
#include <ftw.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

static Snapshot *g_actual_snap = NULL;

void print_snap(Snapshot *snap) {
    printf("Timestamp = %ld\n", snap->timestamp);
    printf("Archivos analizados:\n");
    printf("--------------------\n");
    for (int i = 0; i < snap->cantidad; i++) {
        FileStatus *file = &snap->files[i];
        printf("Path: %s\n", file->path);
        printf("Size: %ld\n", file->size);
        printf("--------------------\n");
    }

}

static int callback_archivo(const char *ruta, const struct stat *info, int tipo, struct FTW *ftwbuf) {
    // Si no es archivo no se analiza
    if (tipo != FTW_F) {
        return 0;
    }

    if (g_actual_snap->cantidad > MAX_FILES) {
        return 0;
    }


    // Se actualiza el estado de los archivos del snap analizado
    FileStatus *file = &g_actual_snap->files[g_actual_snap->cantidad];
    strncpy(file->path, ruta, MAX_PATH - 1);
    file->path[MAX_PATH - 1] = '\0';
    file->size = info->st_size;
    file->timestamp = g_actual_snap->timestamp;

    g_actual_snap->cantidad++;
    return 0;
}

int monitor_scan(const char *base_path, Snapshot *snap) {
  memset(snap, 0, sizeof(Snapshot));
  snap->timestamp = time(NULL);

  // Actualiza variable global
  g_actual_snap = snap;

  // Recorre cada archivo y realiza funcion
  int status = nftw(base_path, callback_archivo, 50, FTW_PHYS);

  // Se elimina variable global
  g_actual_snap = NULL;

  return status;
}
