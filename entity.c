#include <stdlib.h>

#include "entity.h"
#include "renderable.h"

int position_new(struct position **position)
{
    *position = malloc(sizeof(struct position));
    if (*position == NULL)
        return -1;

    (*position)->x = 0.0;
    (*position)->y = 0.0;
    (*position)->z = 0.0;

    return 0;
}

int rotation_new(struct rotation **rotation)
{
    *rotation = malloc(sizeof(struct rotation));
    if (*rotation == NULL)
        return -1;

    (*rotation)->x = 0.0;
    (*rotation)->z = 0.0;

    return 0;
}

int entity_new(
    struct render_descriptor *descriptor,
    struct position *position,
    struct rotation *rotation,
    struct entity **entity)
{
    *entity = malloc(sizeof(struct entity));

    if (position != NULL) {
        (*entity)->position = position;
    } else if (position_new(&((*entity)->position)) < 0) {
        return -1;
    }

    if (rotation != NULL) {
        (*entity)->rotation = rotation;
    } else if (rotation_new(&((*entity)->rotation)) < 0) {
        return -1;
    }

    struct render_descriptor *target_descriptor;
    if (descriptor != NULL) {
        target_descriptor = descriptor;
    } else if (render_descriptor_default(&target_descriptor) < 0) {
        return -1;
    }

    if (renderable_new(target_descriptor, &((*entity)->renderable)) < 0)
        return -1;

    return 0;
}