#include <stdio.h>
#include "uptime.h"

int get_uptime(char *buffer, int size)
{
    FILE *file = fopen("/proc/uptime", "r");

    if (file == NULL) {
        return 1;
    }

    double uptime_seconds;

    if (fscanf(file, "%lf", &uptime_seconds) != 1) {
        fclose(file);
        return 1;
    }

    fclose(file);

    long total_seconds = (long)uptime_seconds;

    long days = total_seconds / 86400;
    long hours = (total_seconds % 86400) / 3600;
    long minutes = (total_seconds % 3600) / 60;

    if (days > 0) {
        snprintf(buffer, size, "%ldd %ldh %ldm", days, hours, minutes);
    }
    else if (hours > 0) {
        snprintf(buffer, size, "%ldh %ldm", hours, minutes);
    }
    else {
        snprintf(buffer, size, "%ldm", minutes);
    }

    return 0;
}
