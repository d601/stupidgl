#include "stupid_engine.h"

int main(int argc, char *argv[])
{
    struct stupid_engine *engine;
    if(stupid_engine_new(engine) < 0)
        return -1;

    return stupid_engine_start(engine);
}
