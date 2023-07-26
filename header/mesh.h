#pragma once
#include "depedencies.h"
#include "glad/glad.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>


class Mesh{
    u32 vao;
    u32 vbo;
    u32 ebo;
    i32 drawType;
public:
    Mesh(i32 drawType);
    ~Mesh();

    void InitializeMesh(f32* verticesData, i32 verticesDataSize, u32* indicesData, i32 indicesDataSize);
    void SendData(f32* verticesData, i32 verticesDataSize, u32* indicesData, i32 indicesDataSize);
    void Draw(i32 indicesSize);
};