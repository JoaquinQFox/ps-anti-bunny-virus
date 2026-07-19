#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <time.h>

#define MAX_PATH 1024
#define MAX_FILES 200

typedef struct {
    char path[MAX_PATH];
    off_t size;
    time_t timestamp;
    int valid;
} FileStatus;

typedef struct {
    FileStatus files[MAX_FILES];
    int cantidad;
    time_t timestamp;
} Snapshot;

#endif
