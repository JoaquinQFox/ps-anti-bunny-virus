#include "detector.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

FileStatus *findFile(Snapshot *snap, char *path) {
    for (int i = 0; i < snap->cantidad; i++) {
        if (strcmp(snap->files[i].path, path) == 0) {
            return &snap->files[i];
        }
    }
    return NULL;
}

int detect_suspicious(Snapshot *last_snap, Snapshot *actual_snap, double umbral, Suspicious *out, int max_out) {
    int found = 0;

    for (int i = 0; i < actual_snap->cantidad; i++) {
        // Se obtiene ultimo estado de archivo leido y el actual tambien
        FileStatus *actual_status = &actual_snap->files[i];
        FileStatus *last_status = findFile(last_snap, actual_status->path);

        off_t last_size = last_status ? last_status->size : 0;
        time_t last_time = last_snap->timestamp;

        // Se calcula el aumento
        double delta_t = difftime(actual_snap->timestamp, last_time);
        if (delta_t <= 0)
            delta_t = 0.001;
        double bytes_rate = (double) (actual_status->size - last_size) / delta_t;

        // Se verifica si hubo un aumento muy grande
        if (bytes_rate > umbral) {
            // Si encuentra lo marca como sospechoso
            if (found < max_out) {
                strncpy(out[found].path, actual_status->path, MAX_PATH - 1);
                out[found].path[MAX_PATH - 1] = '\0';
                out[found].bytes_rate = bytes_rate;
                out[found].actual_size = actual_status->size;
                found++;
            }
        }
    }

    return found;
}
