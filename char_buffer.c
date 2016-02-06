#include <SDL.h>
#include <GL/glew.h>
#include <stdlib.h>
#include <stdio.h>

#include "common.h"
#include "char_buffer.h"

// Null terminated strings are stupid.
// These functions will handle data with the null byte in them.

int char_buffer_new(uint32_t size, struct char_buffer **buffer)
{
    *buffer = malloc(sizeof(struct char_buffer));
    (*buffer)->size = size;
    (*buffer)->buffer = malloc(sizeof(char) * size);
    return 0;
}

int char_buffer_from_file(char *filename, struct char_buffer **buffer)
{
    SDL_RWops *rw_ops = SDL_RWFromFile(filename,"rb");
    if (rw_ops == NULL)
        return -1;

    Sint64 filesize = SDL_RWsize(rw_ops);
    // No idea if this check works correctly
    if (filesize > MAX_BUFFER_SIZE)
        return -1;

    char_buffer_new(filesize, buffer);

    Sint64 bytes_read = 0;
    Sint64 bytes_read_total = 0;
    do {
        bytes_read = SDL_RWread(
            rw_ops,
            (*buffer)->buffer + bytes_read_total,
            1,
            filesize - bytes_read_total);
        bytes_read_total += bytes_read;
    } while ((bytes_read_total < filesize) && (bytes_read != 0));
    
    return 0;
}

void char_buffer_print(struct char_buffer *buffer)
{
    for (uint32_t i = 0; i < buffer->size; i++) {
        printf("%c", (buffer->buffer)[i]);
    }
}

// Tells you if a char buffer's size is safe to cast to a GLint.
// This is more efficient than a specific function for conversion because it's
// just a cast when it works.
// Also, I have no idea if this works correctly.
int char_buffer_fits_in_glint(struct char_buffer *buffer)
{
    return (buffer->size < GLINT_MAX);
}