#include <stdio.h>
#include <stdint.h>
#include <SDL.h>
#include <GL/glew.h>
#include <math.h>
#include <stdlib.h>

#include "shader.h"
#include "char_buffer.h"
#include "matrix.h"
#include "stupid_engine.h"
#include "entity.h"

// Everything outside the main engine code has no business killing the program,
// so these functions aren't exported anywhere.
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

int stupid_engine_process_events(struct stupid_engine *engine)
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                safe_exit_success();
                break;
        }
    }

    return 0;
}

int stupid_engine_init_sdl_opengl(struct stupid_engine *engine)
{
    die_if(
        SDL_Init(SDL_INIT_VIDEO) < 0,
        "SDL_Init failed.");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    engine->window = SDL_CreateWindow(
        "A stupid window",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1024,
        768,
        SDL_WINDOW_OPENGL);
    
    die_if(
        engine->window == NULL,
        "SDL_CreateWindow() failed.");

    // Setup GLEW/GL
    SDL_GLContext gl_context = SDL_GL_CreateContext(engine->window);
    die_if(
        gl_context == NULL,
        "SDL_GL_CreateContext() failed.");

    GLenum err = glewInit();
    die_if(
        err != GLEW_OK,
        "glewInit() failed.");

    printf("Initialization of SDL/OpenGL completed successfully.\n");
    return 0;
}

int stupid_engine_init_camera(struct stupid_engine *engine)
{
    return entity_new(NULL, NULL, NULL, &(engine->camera));
}

int stupid_engine_new(struct stupid_engine **engine)
{
    *engine = malloc(sizeof(struct stupid_engine));
    if (*engine == NULL)
        return -1;

    return 0;
}

int stupid_engine_start(struct stupid_engine *engine)
{
    stupid_engine_init_sdl_opengl(engine);

    die_if(
        stupid_engine_init_camera(engine) < 0,
        "Failed to init camera");

    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Create vertex array
    GLuint vertex_array_id;
    glGenVertexArrays(1, &vertex_array_id);
    glBindVertexArray(vertex_array_id);

    // Load shaders
    GLuint program_id;
    load_shaders(&program_id);

    // Create vertex buffer
    GLfloat g_vertex_buffer_data[] = {
        -32.0f, -8.0f, -4.0f,
        8.0f, -8.0f, -4.0f,
        0.0f,  8.0f, -4.0f,
     };

    GLuint vertex_buffer;
    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(g_vertex_buffer_data),
        g_vertex_buffer_data,
        GL_STATIC_DRAW);

    // Bind variables to their location in the shaders
    GLint gScale_location = glGetUniformLocation(program_id, "gScale");
    /*
    die_if(
        gScale_location == 0xFFFFFFFF,
        "No gScale location");
    */

    GLint projection_matrix_location = glGetUniformLocation(program_id, "projection_matrix");
    die_if(
        projection_matrix_location == 0xFFFFFFFF,
        "No projection matrix location");

    float scale = 0.0;
    float rotation = 0.0;
    float *projection_matrix;
    float *rotation_matrix;
    float *world_matrix;
    matrix_b_new(4, 4, &projection_matrix);
    matrix_b_new(4, 4, &rotation_matrix);
    matrix_b_new(4, 4, &world_matrix);

    matrix_set_perspective(-32.0, -16.0, 3.0, 32.0, 16.0, 32.0, &projection_matrix);

    for (;;) {
        stupid_engine_process_events(engine);

        rotation += 0.01;
        matrix_set_rotation_y(rotation, &rotation_matrix);

        scale += 0.01;
        glUniform1f(gScale_location, sinf(scale));
        
        matrix_multiply(
            4, 4, rotation_matrix,
            4, 4, projection_matrix,
            NULL, NULL, &world_matrix);

        glUniformMatrix4fv(projection_matrix_location, 1, GL_FALSE, &world_matrix[0]);
        
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program_id);

        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
        glVertexAttribPointer(
           0,
           3,
           GL_FLOAT,
           GL_FALSE,           
           0,
           (void*) 0
        );
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glDisableVertexAttribArray(0);

        SDL_GL_SwapWindow(engine->window);
        SDL_Delay(10);
    }
    
    // Cleanup
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array_id);

    safe_exit_success();
}
