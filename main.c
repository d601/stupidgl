#include "stupid_engine.h"

int main(int argc, char *argv[])
{
    struct stupid_engine *engine;
    stupid_engine_new(engine);
    return stupid_engine_start(engine);
}
