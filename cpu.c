#include <stdio.h>
#include <string.h>
#include "cpu.h"

int get_cpu_name(char *buffer, int size)
{
    FILE *file = fopen("/proc/cpuinfo", "r");

    if (file == NULL) {
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "model name", 10) == 0) {
            char *value = strchr(line, ':');

            if (value == NULL) {
                continue;
            }

            value++;

            while (*value == ' ' || *value == '\t') {
                value++;
            }

            strncpy(buffer, value, size - 1);
            buffer[size - 1] = '\0';

            size_t length = strlen(buffer);

            if (length > 0 && buffer[length - 1] == '\n') {
                buffer[length - 1] = '\0';
            }

            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
