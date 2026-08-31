#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "packages.h"

static int command_exists(const char *command)
{
    char check[256];

    snprintf(
        check,
        sizeof(check),
        "command -v %s >/dev/null 2>&1",
        command
    );

    return system(check) == 0;
}

static int run_package_command(
    char *buffer,
    size_t size,
    const char *command,
    const char *manager
)
{
    FILE *file;
    char line[256];

    file = popen(command, "r");

    if (file == NULL) {
        return -1;
    }

    if (fgets(line, sizeof(line), file) == NULL) {
        pclose(file);
        return -1;
    }

    pclose(file);

    line[strcspn(line, "\n")] = '\0';

    snprintf(buffer, size, "%s (%s)", line, manager);

    return 0;
}

int get_packages(char *buffer, size_t size)
{
    /* Arch / Artix / Or any other distro which uses pacman */
    if (command_exists("pacman")) {
        return run_package_command(
            buffer,
            size,
            "pacman -Qq | wc -l",
            "pacman"
        );
    }

    /* Gentoo */
    if (command_exists("qlist")) {
        return run_package_command(
            buffer,
            size,
            "qlist -I | wc -l",
            "portage"
        );
    }

    /* Debian / Ubuntu / derivatives */
    if (command_exists("dpkg-query")) {
        return run_package_command(
            buffer,
            size,
            "dpkg-query -W -f='${binary:Package}\\n' | wc -l",
            "dpkg"
        );
    }

    /* Fedora / RHEL / derivatives */
    if (command_exists("dnf")) {
        return run_package_command(
            buffer,
            size,
            "dnf list installed 2>/dev/null | tail -n +2 | wc -l",
            "dnf"
        );
    }

    /* Alpine */
    if (command_exists("apk")) {
        return run_package_command(
            buffer,
            size,
            "apk info | wc -l",
            "apk"
        );
    }

    return -1;
}
