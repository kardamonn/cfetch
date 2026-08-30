#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logo.h"

const char *get_logo_color(void)
{
    static char color[16];
    const char *home = getenv("HOME");

    if (home == NULL)
        return "\033[0m";

    char path[512];

    snprintf(
        path,
        sizeof(path),
        "%s/.config/cfetch/config",
        home
    );

    FILE *file = fopen(path, "r");

    if (file == NULL)
        return "\033[0m";

    char line[64];

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, "logo_color=", 11) != 0)
            continue;

        char *value = line + 11;
        value[strcspn(value, "\n")] = '\0';

        if (strcmp(value, "black") == 0)
            strcpy(color, "\033[30m");
        else if (strcmp(value, "red") == 0)
            strcpy(color, "\033[31m");
        else if (strcmp(value, "green") == 0)
            strcpy(color, "\033[32m");
        else if (strcmp(value, "yellow") == 0)
            strcpy(color, "\033[33m");
        else if (strcmp(value, "blue") == 0)
            strcpy(color, "\033[34m");
        else if (strcmp(value, "magenta") == 0)
            strcpy(color, "\033[35m");
        else if (strcmp(value, "cyan") == 0)
            strcpy(color, "\033[36m");
        else if (strcmp(value, "white") == 0)
            strcpy(color, "\033[37m");
        else
            strcpy(color, "\033[0m");

        fclose(file);
        return color;
    }

    fclose(file);
    return "\033[0m";
}
