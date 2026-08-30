#include <stdio.h>
#include <string.h>

#include "output.h"
#include "logo.h"

#define MIN_LOGO_WIDTH 11
#define MIN_INFO_WIDTH 30

#define COLOR_BORDER "\033[35m"
#define COLOR_LABEL  "\033[36m"
#define COLOR_RESET  "\033[0m"

static size_t get_logo_width(void)
{
    size_t max_width = 0;
    int height = get_logo_height();

    for (int i = 0; i < height; i++) {
        const char *line = get_logo_line(i);

        if (line == NULL)
            continue;

        size_t width = strlen(line);

        if (width > max_width)
            max_width = width;
    }

    if (max_width < MIN_LOGO_WIDTH)
        max_width = MIN_LOGO_WIDTH;

    return max_width;
}

static size_t get_info_width(const InfoItem *items, size_t count)
{
    size_t max_width = 0;

    for (size_t i = 0; i < count; i++) {
        size_t width =
            strlen(items[i].label) +
            1 +
            strlen(items[i].value);

        if (width > max_width)
            max_width = width;
    }

    if (max_width < MIN_INFO_WIDTH)
        max_width = MIN_INFO_WIDTH;

    return max_width;
}

static void print_border(size_t logo_width, size_t info_width)
{
    printf(COLOR_BORDER "+");

    for (size_t i = 0; i < logo_width + 2; i++)
        putchar('-');

    printf("+");

    for (size_t i = 0; i < info_width + 2; i++)
        putchar('-');

    printf("+\n" COLOR_RESET);
}

void print_info(const InfoItem *items, size_t count)
{
    size_t logo_width = get_logo_width();
    size_t info_width = get_info_width(items, count);

    int logo_height = get_logo_height();

    size_t rows = count;

    if (logo_height > (int)rows)
        rows = logo_height;

    /*
     * Top border
     */
    print_border(logo_width, info_width);

    /*
     * Information rows
     */
    for (size_t i = 0; i < rows; i++) {
        const char *logo_line = get_logo_line((int)i);

        if (logo_line == NULL)
            logo_line = "";

        /*
         * Left side: logo
         */
        printf(COLOR_BORDER "| " COLOR_RESET);
        printf("%-*s", (int)logo_width, logo_line);
        printf(COLOR_BORDER " |" COLOR_RESET);

        /*
         * Right side: system information
         */
        if (i < count) {
            size_t value_length = strlen(items[i].value);

            printf(" " COLOR_LABEL "%-10s" COLOR_RESET " %s",
                   items[i].label,
                   items[i].value);

            /*
             * Pad the right side so the border stays aligned.
             */
            size_t used = 1 + 10 + 1 + value_length;

            if (used < info_width) {
                for (size_t j = used; j < info_width; j++)
                    putchar(' ');
            }

            putchar(' ');
        } else {
            printf(" %-*s ", (int)info_width, "");
        }

        printf(COLOR_BORDER "|" COLOR_RESET "\n");
    }

    /*
     * Bottom border
     */
    print_border(logo_width, info_width);
}
