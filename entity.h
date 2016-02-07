#pragma once

#include "renderable.h"

struct position {
    float x;
    float y;
    float z;
};

// I should be using quaternions but I need to understand how those work first.
// This version is totally halfassed and should just be a placeholder.
struct rotation {
    float x;
    float z;
};

struct entity {
    struct renderable *renderable;
    struct position *position;
    struct rotation *rotation;
};

int entity_new(
    struct render_descriptor *descriptor,
    struct position *position,
    struct rotation *rotation,
    struct entity **entity);