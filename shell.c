#include <stdlib.h>
#include <string.h>

#include "shell.h"

int get_shell(char *buffer, size_t size)
{
    const char *shell = getenv("SHELL");

    if (shell == NULL || shell[0] == '\0') {
        return -1;
    }

    const char *name = strrchr(shell, '/');

    if (name != NULL) {
        name++;
    } else {
        name = shell;
    }

    if (strlen(name) >= size) {
        return -1;
    }

    strcpy(buffer, name);

    return 0;
}
