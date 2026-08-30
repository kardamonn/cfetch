#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include <unistd.h>
#include "system.h"

int get_kernel(char *buffer, int size)
{
    struct utsname system_info;

    if (uname(&system_info) != 0) {
        return 1;
    }

    strncpy(buffer, system_info.release, size - 1);
    buffer[size - 1] = '\0';

    return 0;
}

int get_hostname(char *buffer, int size)
{
    if (gethostname(buffer, size) != 0) {
        return 1;
    }

    buffer[size - 1] = '\0';

    return 0;
}
