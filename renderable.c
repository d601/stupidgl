#include <stdlib.h>

#include "renderable.h"

int render_descriptor_default(struct render_descriptor **descriptor)
{
    // This should be a singleton
    *descriptor = malloc(sizeof(struct render_descriptor));
    if (*descriptor == NULL)
        return -1;

    (*descriptor)->type = NONE;
    (*descriptor)->contents.nothing = 0;
    return 0;
}

int renderable_new(struct render_descriptor *descriptor, struct renderable **renderable)
{
    *renderable = malloc(sizeof(renderable));
    if (*renderable == NULL)
        return -1;

    (*renderable)->descriptor = descriptor;
    (*renderable)->data = malloc(sizeof(struct render_data));
    if ((*renderable)->data == NULL)
        return -1;

    return 0;
}