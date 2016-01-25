#version 300 es
in vec3 position;

void main() {
    gl_Position.xyz = position;
    gl_Position.w = 1.0;
}
