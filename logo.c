#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "logo.h"

#define MAX_LINE_LENGTH 4096

static char *logo_lines[LOGO_HEIGHT];
static int logo_line_count = 0;

static const char *default_logo[] = {
    " /\\_/\\",
    "( o.o )",
    " > ^ <"
};

void load_logo(void)
{
    const char *home = getenv("HOME");

    logo_line_count = 0;

    if (home != NULL) {
        char path[4096];

        snprintf(
            path,
            sizeof(path),
            "%s/.config/cfetch/logo.txt",
            home
        );

        FILE *file = fopen(path, "r");

        if (file != NULL) {
            char buffer[MAX_LINE_LENGTH];

            while (
                logo_line_count < LOGO_HEIGHT &&
                fgets(buffer, sizeof(buffer), file) != NULL
            ) {
                buffer[strcspn(buffer, "\n")] = '\0';

                logo_lines[logo_line_count] = strdup(buffer);

                if (logo_lines[logo_line_count] != NULL)
                    logo_line_count++;
            }

            fclose(file);
        }
    }

    if (logo_line_count == 0) {
        for (
            size_t i = 0;
            i < sizeof(default_logo) / sizeof(default_logo[0]);
            i++
        ) {
            logo_lines[i] = strdup(default_logo[i]);

            if (logo_lines[i] != NULL)
                logo_line_count++;
        }
    }
}

const char *get_logo_line(int line)
{
    if (line < 0 || line >= logo_line_count)
        return "";

    return logo_lines[line];
}

int get_logo_height(void)
{
    return logo_line_count;
}

void free_logo(void)
{
    for (int i = 0; i < logo_line_count; i++) {
        free(logo_lines[i]);
        logo_lines[i] = NULL;
    }

    logo_line_count = 0;
}

static const char *get_config_color(const char *option)
{
    static char color[16];
    const char *home = getenv("HOME");

    if (home == NULL)
        return "\033[0m";

    char path[4096];

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
    char key[32];

    snprintf(key, sizeof(key), "%s=", option);

    while (fgets(line, sizeof(line), file) != NULL) {
        if (strncmp(line, key, strlen(key)) != 0)
            continue;

        char *value = line + strlen(key);

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

const char *get_logo_color(void)
{
    return get_config_color("logo_color");
}

const char *get_border_color(void)
{
    return get_config_color("border_color");
}

const char *get_label_color(void)
{
    return get_config_color("label_color");
}
