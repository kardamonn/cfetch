#ifndef OUTPUT_H
#define OUTPUT_H

#include <stddef.h>

typedef struct {
    const char *label;
    const char *value;
} InfoItem;

void print_info(const InfoItem *items, size_t count);

#endif
