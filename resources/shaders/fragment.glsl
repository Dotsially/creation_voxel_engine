#version 460 core

in vec3 fragcolor;
out vec4 fragColor;

void main(){
    fragColor = vec4(fragcolor/32, 1.0);

}