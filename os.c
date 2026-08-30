#include <stdio.h>
#include <string.h>
#include "os.h"

int get_os_name(char *buffer, int size)
{
    FILE *file = fopen("/etc/os-release", "r");

    if (file == NULL) {
        return 1;
    }

    char line[256];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "PRETTY_NAME=", 12) == 0) {
            char *value = line + 12;

            if (value[0] == '"') {
                value++;
            }

            strncpy(buffer, value, size - 1);
            buffer[size - 1] = '\0';

            size_t length = strlen(buffer);

            if (length > 0 && buffer[length - 1] == '\n') {
                buffer[length - 1] = '\0';
                length--;
            }

            if (length > 0 && buffer[length - 1] == '"') {
                buffer[length - 1] = '\0';
            }

            fclose(file);
            return 0;
        }
    }

    fclose(file);
    return 1;
}
