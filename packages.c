#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "packages.h"

int get_packages(char *buffer, size_t size)
{
    FILE *file;
    char line[256];

    if (access("/usr/bin/pacman", F_OK) == 0) {
        file = popen("pacman -Qq | wc -l", "r");

        if (file == NULL) {
            return -1;
        }

        if (fgets(line, sizeof(line), file) == NULL) {
            pclose(file);
            return -1;
        }

        pclose(file);

        line[strcspn(line, "\n")] = '\0';

        snprintf(buffer, size, "%s (pacman)", line);

        return 0;
    }

    return -1;
}
