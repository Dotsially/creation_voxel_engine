#version 460 core

in vec2 pos;

layout (location = 1) uniform mat4 projection;
layout (location = 2) uniform mat4 view;
layout (location = 0) uniform mat4 transform;

const vec2 uv_coords[4] = vec2[4](
    vec2(0, 0), vec2(0, 1),
    vec2(1, 1), vec2(1, 0)
);

const int uv_indices[6] = int[6](
    0, 1, 2, 3, 0, 2
);

out vec2 uv;

void main(){
    uv = uv_coords[uv_indices[gl_VertexID%6]];
    gl_Position = projection * view * transform * vec4(pos,0.5,1.0);
}

