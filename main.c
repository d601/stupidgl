#include <stdio.h>
#include <SDL.h>
#include <GL/glew.h>

void safe_exit()
{
    SDL_Quit();
}

void safe_exit_success()
{
    safe_exit();
    exit(0);
}

void safe_exit_fail()
{
    safe_exit();
    exit(-1);
}

void die_if(int condition, char *message)
{
    if (!condition)
        return;

    printf(message);
    safe_exit_fail();
}

int main(int argc, char *argv[])
{
    int return_status;

    die_if(
        SDL_Init(SDL_INIT_VIDEO) < 0,
        "SDL_Init failed.");

    // Unclear where exactly these should be set.
    // Also, need to check for errors.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    SDL_Window *window = SDL_CreateWindow(
        "A stupid window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        SDL_WINDOW_OPENGL);
    die_if(
        window == NULL,
        "SDL_CreateWindow() failed.");

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    die_if(
        gl_context == NULL,
        "SDL_GL_CreateContext() failed.");

    GLenum err = glewInit();
    die_if(
        err != GLEW_OK,
        "glewInit() failed.");

    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(window);

    SDL_Delay(1000);
    
    safe_exit_success();
}
