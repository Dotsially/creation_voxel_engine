#pragma once 
#include "depedencies.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include "camera.h"
#include "world.h"
#include "tile.h"

class BlockHandler{
    u16 currentBlock = grass.tileID;
    glm::ivec3 block;
    glm::ivec3 blockNormal;
    bool isSolid = false;
    void Raycast(Camera* camera, glm::vec3 rayDirection, World* chunk);

public:
    void Update(Camera* camera, World* chunk, const u8* keystate);
    glm::ivec3 GetBlock();
    bool IsSolid();
};