#pragma once 
#include "depedencies.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "camera.h"
#include "chunk.h"

class BlockHandler{
    glm::ivec3 block;
    glm::ivec3 blockNormal;
    bool isSolid = false;
    void Raycast(Camera* camera, Chunk* chunk);

public:
    void Update(Camera* camera, Chunk* chunk);
    glm::ivec3 GetBlock();
    bool IsSolid();
};