#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include "gpu.h"

struct gpu_id {
    const char *vendor;
    const char *device;
    const char *name;
};

static const struct gpu_id gpu_table[] = {
    /* Intel */
    {"0x8086", "0x1616", "Intel HD Graphics 5500"},
    {"0x8086", "0x22b1", "Intel HD Graphics"},
    {"0x8086", "0x0f31", "Intel HD Graphics 400"},
    {"0x8086", "0x0046", "Intel HD Graphics"},

    /* AMD */
    {"0x1002", "0x73ff", "AMD Radeon RX 6600"},
};

static const int gpu_table_size =
    sizeof(gpu_table) / sizeof(gpu_table[0]);

int get_gpu_name(char *buffer, int size)
{
    DIR *dir = opendir("/sys/class/drm");

    if (dir == NULL) {
        return 1;
    }

    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strncmp(entry->d_name, "card", 4) != 0) {
            continue;
        }

        if (strchr(entry->d_name, '-') != NULL) {
            continue;
        }

        char vendor_path[512];
        char device_path[512];

        snprintf(
            vendor_path,
            sizeof(vendor_path),
            "/sys/class/drm/%s/device/vendor",
            entry->d_name
        );

        snprintf(
            device_path,
            sizeof(device_path),
            "/sys/class/drm/%s/device/device",
            entry->d_name
        );

        FILE *vendor_file = fopen(vendor_path, "r");
        FILE *device_file = fopen(device_path, "r");

        if (vendor_file == NULL || device_file == NULL) {
            if (vendor_file != NULL)
                fclose(vendor_file);

            if (device_file != NULL)
                fclose(device_file);

            continue;
        }

        char vendor[32];
        char device[32];

        if (fscanf(vendor_file, "%31s", vendor) != 1 ||
            fscanf(device_file, "%31s", device) != 1) {

            fclose(vendor_file);
            fclose(device_file);
            continue;
        }

        fclose(vendor_file);
        fclose(device_file);

        for (int i = 0; i < gpu_table_size; i++) {
            if (strcmp(vendor, gpu_table[i].vendor) == 0 &&
                strcmp(device, gpu_table[i].device) == 0) {

                snprintf(buffer, size, "%s", gpu_table[i].name);

                closedir(dir);
                return 0;
            }
        }

        snprintf(
            buffer,
            size,
            "Unknown GPU (%s:%s)",
            vendor,
            device
        );

        closedir(dir);
        return 0;
    }

    closedir(dir);
    return 1;
}
