#pragma once

#include <stdint.h>

struct render_data {
    int placeholder;
};

enum render_type {
    NONE,
    GRID
};

struct render_descriptor_grid {
    float width;
    float height;
    uint8_t horizontal_divisions;
    uint8_t vertical_divisions;
};

struct render_descriptor {
    enum render_type type;
    union {
        // No idea how to say that a union might be empty
        uint8_t nothing;
        struct render_descriptor_grid *grid;
    } contents;
};

struct renderable {
    struct render_descriptor *descriptor;
    struct render_data *data;
};

int render_descriptor_default(struct render_descriptor **descriptor);

int renderable_new(struct render_descriptor *descriptor, struct renderable **renderable);