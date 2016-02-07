#pragma once

#include <SDL.h>

struct stupid_engine {
    SDL_Window *window;
    struct entity *camera;
};

int stupid_engine_new(struct stupid_engine **engine);

int stupid_engine_start(struct stupid_engine *engine);