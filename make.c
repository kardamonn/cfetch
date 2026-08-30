#include <stdio.h>
#include <string.h>

#include "os.h"
#include "system.h"
#include "cpu.h"
#include "memory.h"
#include "uptime.h"
#include "output.h"
#include "gpu.h"

int main(int argc, char *argv[])
{
    int color_enabled = 1;

    if (argc > 1 && strcmp(argv[1], "--no-color") == 0) {
        color_enabled = 0;
    }

    set_color_enabled(color_enabled);

    char os_name[256];
    char kernel[256];
    char hostname[256];
    char cpu_name[256];
    char memory[256];
    char uptime[256];
    char gpu_name[256];

    if (get_os_name(os_name, sizeof(os_name)) != 0) {
        snprintf(os_name, sizeof(os_name), "Unknown");
    }

    if (get_kernel(kernel, sizeof(kernel)) != 0) {
        snprintf(kernel, sizeof(kernel), "Unknown");
    }

    if (get_hostname(hostname, sizeof(hostname)) != 0) {
        snprintf(hostname, sizeof(hostname), "Unknown");
    }

    if (get_cpu_name(cpu_name, sizeof(cpu_name)) != 0) {
        snprintf(cpu_name, sizeof(cpu_name), "Unknown");
    }

    if (get_memory(memory, sizeof(memory)) != 0) {
        snprintf(memory, sizeof(memory), "Unknown");
    }

    if (get_uptime(uptime, sizeof(uptime)) != 0) {
        snprintf(uptime, sizeof(uptime), "Unknown");
    }

    if (get_gpu_name(gpu_name, sizeof(gpu_name)) != 0) {
        snprintf(gpu_name, sizeof(gpu_name), "Unknown");
    }

    print_info(
        os_name,
        kernel,
        hostname,
        cpu_name,
        gpu_name,
        memory,
        uptime
    );

    return 0;
}
