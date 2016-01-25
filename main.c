#include <stdio.h>
#include <SDL.h>
#include <GL/glew.h>

#include <stdint.h>

#include "shader.h"
#include "char_buffer.h"

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
    
    glClearColor(0.0, 0.0, 0.0, 0.0);

    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    GLuint program_id;
    load_shaders(&program_id);

    GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
     };

    GLuint vertex_buffer;
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertex_buffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    // Give our vertices to OpenGL.
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(g_vertex_buffer_data),
        g_vertex_buffer_data,
        GL_STATIC_DRAW);


    // Loop starts (?)
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program_id);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );
    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);

    SDL_GL_SwapWindow(window);
    
    // Cleanup
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array_id);
    SDL_Delay(1000);

    safe_exit_success();
}
