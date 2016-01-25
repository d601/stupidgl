#include <GL/glew.h>
#include <stdio.h>

#include "shader.h"
#include "char_buffer.h"

void adebug_gl(int line)
{
    printf("shader %d: %d\n", line, glGetError());
}

GLuint load_shader(char *filename, GLenum shader_type, GLuint *shader_id) {
    struct char_buffer *shader_buffer;
    char_buffer_from_file(filename, &shader_buffer);
    *shader_id = glCreateShader(shader_type);

    // Casting to const char is probably bad
    glShaderSource(
        *shader_id,
        1,
        (const char **) &(shader_buffer->buffer),
        &(shader_buffer->size));

    GLint result = GL_FALSE;
    glCompileShader(*shader_id);
    adebug_gl(__LINE__);
    glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &result);

    printf("--> %d\n", result);

    GLint info_log_length = 0;
    glGetShaderiv(*shader_id, GL_INFO_LOG_LENGTH, &info_log_length);
    adebug_gl(__LINE__);
    printf("* %d\n", info_log_length);

    if (info_log_length > 0) {
        struct char_buffer *log_buffer;
        char_buffer_new(info_log_length + 1, &log_buffer);
        glGetShaderInfoLog(*shader_id, info_log_length, NULL, log_buffer->buffer);
        char_buffer_print(log_buffer);
    }

    return result;
}

GLuint load_shaders(GLuint *program_id)
{
    // Do I need to initialize these?
    GLuint vertex_shader_id;
    GLuint fragment_shader_id;
    load_shader("shaders/vertex.vert", GL_VERTEX_SHADER, &vertex_shader_id);
    adebug_gl(__LINE__);
    load_shader("shaders/fragment.frag", GL_FRAGMENT_SHADER, &fragment_shader_id);
    adebug_gl(__LINE__);

    *program_id = glCreateProgram();
    glAttachShader(*program_id, vertex_shader_id);
    adebug_gl(__LINE__);
    glAttachShader(*program_id, fragment_shader_id);
    adebug_gl(__LINE__);


    // Fix the shader to work on 3.00
    glBindAttribLocation(*program_id, 0, "position");

    glLinkProgram(*program_id);
    adebug_gl(__LINE__);

    // Check the program
    GLint result = GL_FALSE;
    glGetProgramiv(*program_id, GL_LINK_STATUS, &result);
    adebug_gl(__LINE__);
    printf("--> %d\n", result);
    GLint info_log_length = 0;
    glGetProgramiv(*program_id, GL_INFO_LOG_LENGTH, &info_log_length);
    adebug_gl(__LINE__);
    printf("* %d\n", info_log_length);

    if (info_log_length > 0) {
        struct char_buffer *log_buffer;
        char_buffer_new(info_log_length + 1, &log_buffer);
        glGetProgramInfoLog(*program_id, info_log_length, NULL, log_buffer->buffer);
        char_buffer_print(log_buffer);
    }

    glDetachShader(*program_id, vertex_shader_id);
    adebug_gl(__LINE__);
    glDetachShader(*program_id, fragment_shader_id);
    adebug_gl(__LINE__);

    glDeleteShader(vertex_shader_id);
    adebug_gl(__LINE__);
    glDeleteShader(fragment_shader_id);
    adebug_gl(__LINE__);

    return 0;
}
