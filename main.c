#include <stdio.h>

#include "os.h"
#include "system.h"
#include "cpu.h"
#include "memory.h"
#include "uptime.h"
#include "output.h"
#include "gpu.h"
#include "logo.h"
#include "shell.h"
#include "packages.h"
#include "timeinfo.h"

int main(void)
{
    char os_name[256];
    char kernel[256];
    char hostname[256];
    char cpu_name[256];
    char memory[256];
    char uptime[256];
    char gpu_name[256];
    char shell[256];
    char packages[256];
    char date[256];
    char time[256];

    get_os_name(os_name, sizeof(os_name));
    get_kernel(kernel, sizeof(kernel));
    get_hostname(hostname, sizeof(hostname));
    get_cpu_name(cpu_name, sizeof(cpu_name));
    get_memory(memory, sizeof(memory));
    get_uptime(uptime, sizeof(uptime));
    get_gpu_name(gpu_name, sizeof(gpu_name));
    get_shell(shell, sizeof(shell));
    get_packages(packages, sizeof(packages));
    get_date(date, sizeof(date));
    get_time(time, sizeof(time));

    load_logo();

    InfoItem items[] = {
        {"OS:", os_name},
        {"Kernel:", kernel},
        {"Hostname:", hostname},
        {"CPU:", cpu_name},
        {"GPU:", gpu_name},
        {"Memory:", memory},
        {"Uptime:", uptime},
        {"Shell:", shell},
        {"Packages:", packages},
        {"Date:", date},
        {"Time:", time}
    };

    print_info(items, sizeof(items) / sizeof(items[0]));

    free_logo();

    return 0;
}
