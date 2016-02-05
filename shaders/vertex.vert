#version 300 es
//uniform float gScale;
uniform mat4 projection_matrix;
in vec3 position;
//out vec3 pos_color;

void main() {
    //gl_Position = vec4(position.x * gScale, position.y * gScale, position.z, 1.0);
    //gl_Position = projection_matrix * vec4(position, 1.0);
    gl_Position = projection_matrix * vec4(position, 1.0);
    //pos_color = vec3(clamp(position, 0.0, 1.0));
}
