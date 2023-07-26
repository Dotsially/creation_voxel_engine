#version 460 core

in vec3 pos;

layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 view;
layout (location = 0) uniform mat4 transform;

out vec3 fragcolor;

void main(){
    gl_Position = projection * view * transform * vec4(pos, 1.0);
    fragcolor = pos;
}