#version 300 es
precision highp float;
uniform float gScale;

in vec3 pos_color;
out vec3 color;
void main(){
  //color = vec3(gScale,1.0 - gScale,gScale - 1.0);
    //color = vec3(pos_color.x, gScale - pos_color.y, pos_color.z);
    color = pos_color;
}

