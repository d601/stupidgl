#pragma once
#include <stdint.h>

#define MAX_BUFFER_SIZE (UINT32_MAX)

struct char_buffer
{
    uint32_t size;
    char *buffer;
};

int char_buffer_new(uint32_t size, struct char_buffer **buffer);
int char_buffer_from_file(char *filename, struct char_buffer **buffer);
void char_buffer_print(struct char_buffer *buffer);
