#include <stdio.h>
#include <time.h>

#include "timeinfo.h"

int get_date(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    if (local == NULL) {
        return -1;
    }

    if (strftime(buffer, size, "%Y-%m-%d", local) == 0) {
        return -1;
    }

    return 0;
}

int get_time(char *buffer, size_t size)
{
    time_t now = time(NULL);
    struct tm *local = localtime(&now);

    if (local == NULL) {
        return -1;
    }

    if (strftime(buffer, size, "%H:%M:%S", local) == 0) {
        return -1;
    }

    return 0;
}
