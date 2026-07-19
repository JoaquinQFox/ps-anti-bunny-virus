#ifndef MONITOR_H
#define MONITOR_H

#include <stdio.h>
#include <time.h>

#define MAX_PATH 1024
#define MAX_FILES 4096

typedef struct {
    char path[MAX_PATH];
    off_t size;
    time_t timestamp;
} FileStatus;

typedef struct {
    FileStatus files[MAX_FILES];
    int cantidad;
    time_t timestamp;
} Snapshot;

int monitor_scan(const char *base_path, Snapshot *snap);

void print_snap(Snapshot *snap);

#endif
