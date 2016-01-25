#include <GL/glew.h>
#include <stdio.h>

#include "shader.h"
#include "char_buffer.h"

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
    glGetShaderiv(*shader_id, GL_COMPILE_STATUS, &result);

    GLint info_log_length = 0;
    glGetShaderiv(*shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

    if (info_log_length > 1) {
        struct char_buffer *log_buffer;
        char_buffer_new(info_log_length, &log_buffer);
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
    load_shader("shaders/fragment.frag", GL_FRAGMENT_SHADER, &fragment_shader_id);

    *program_id = glCreateProgram();
    glAttachShader(*program_id, vertex_shader_id);
    glAttachShader(*program_id, fragment_shader_id);

    glBindAttribLocation(*program_id, 0, "position");

    glLinkProgram(*program_id);

    // Check the program
    GLint result = GL_FALSE;
    glGetProgramiv(*program_id, GL_LINK_STATUS, &result);

    GLint info_log_length = 0;
    glGetProgramiv(*program_id, GL_INFO_LOG_LENGTH, &info_log_length);

    // Log length contains null terminator
    if (info_log_length > 1) {
        struct char_buffer *log_buffer;
        char_buffer_new(info_log_length, &log_buffer);
        glGetProgramInfoLog(*program_id, info_log_length, NULL, log_buffer->buffer);
        char_buffer_print(log_buffer);
    }

    glDetachShader(*program_id, vertex_shader_id);
    glDetachShader(*program_id, fragment_shader_id);

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    return 0;
}
