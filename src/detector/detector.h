#ifndef DETECTOR_H
#define DETECTOR_H

#include "../monitor/monitor.h"
#include <sys/stat.h>

typedef struct {
    char path[MAX_PATH];
    double bytes_rate;
    off_t actual_size;
} Suspicious;

int detect_suspicious(Snapshot *last, Snapshot *actual, double umbral,
                                        Suspicious *out, int max_out);

#endif
