#include <stdio.h>
#include <string.h>
#include "memory.h"

int get_memory(char *buffer, int size)
{
    FILE *file = fopen("/proc/meminfo", "r");

    if (file == NULL) {
        return 1;
    }

    char line[256];
    unsigned long mem_total = 0;
    unsigned long mem_available = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "MemTotal:", 9) == 0) {
            sscanf(line + 9, "%lu", &mem_total);
        }
        else if (strncmp(line, "MemAvailable:", 13) == 0) {
            sscanf(line + 13, "%lu", &mem_available);
        }

        if (mem_total != 0 && mem_available != 0) {
            break;
        }
    }

    fclose(file);

    if (mem_total == 0 || mem_available == 0) {
        return 1;
    }

    unsigned long mem_used = mem_total - mem_available;

    snprintf(
        buffer,
        size,
        "%.1f GiB / %.1f GiB",
        mem_used / 1048576.0,
        mem_total / 1048576.0
    );

    return 0;
}
