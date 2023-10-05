#include "block_handler.h"
#include "iostream"


void BlockHandler::Update(Camera* camera, World* world, const u8* keystate){
    if(keystate[SDL_SCANCODE_1]){
        currentBlock = grass.tileID;
    }
    else if(keystate[SDL_SCANCODE_2]){
        currentBlock = dirt.tileID;
    }
    else if(keystate[SDL_SCANCODE_3]){
        currentBlock = stone.tileID;
    }

    i32 x,y;
    SDL_GetMouseState(&x,&y);
    // std::cout << x << " ";
    // std::cout << y << std::endl;

    //Get ray from mouse coordinates in 3d space
    glm::vec3 rayNds = glm::vec3((2.0f * x) / 1280.0f - 1.0f, 1.0f - (2.0f * y) / 720.0f, 1.0f);
    glm::vec4 rayClip = glm::vec4(rayNds.x, rayNds.y, -1.0, 1.0);
    glm::vec4 rayEye = glm::inverse(camera->GetProjectMatrix()) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);
    glm::vec4 temp = (glm::inverse(camera->GetViewMatrix()) * rayEye);
    glm::vec3 rayWor = glm::vec3(temp.x, temp.y, temp.z);
    rayWor = glm::normalize(rayWor);

    if(SDL_GetMouseState(&x,&y) & SDL_BUTTON_LMASK ){
        if(isSolid){
            world->RemoveBlock(block.x,block.y,block.z);
        }
    }
    else if(SDL_GetMouseState(&x,&y) & SDL_BUTTON_RMASK ){
        if(isSolid){
            world->AddBlock(block.x + blockNormal.x, block.y + blockNormal.y, block.z + blockNormal.z, currentBlock);
        }
    }


    Raycast(camera, rayWor, world);
}


void BlockHandler::Raycast(Camera* camera, glm::vec3 rayDirection, World* world){
    isSolid = false;
    f32 deltaX, deltaY, deltaZ, maxX, maxY, maxZ;
    
    glm::vec3 pos1 = camera->GetPosition();
    glm::vec3 pos2 = camera->GetPosition() + rayDirection * 20.0f;



    i32 stepDir = -1;
    blockNormal = glm::vec3(0);

    i32 dx = glm::sign(pos2.x - pos1.x);
    if(dx != 0){
        deltaX = glm::min(dx / (pos2.x - pos1.x), 10000000.0f);
    }else{
        deltaX = 10000000.0f;
    }
    if(dx > 0){
        maxX = deltaX * (1.0f - glm::fract(pos1.x));
    }else{
        maxX = deltaX * glm::fract(pos1.x);
    }
    block.x = (i32)pos1.x;

    i32 dy = glm::sign(pos2.y - pos1.y);
    if(dy != 0){
        deltaY = glm::min(dy / (pos2.y - pos1.y), 10000000.0f);
    }else{
        deltaY = 10000000.0f;
    }
    if(dy > 0){
        maxY = deltaY * (1.0f - glm::fract(pos1.y));
    }else{
        maxY = deltaY * glm::fract(pos1.y);
    }
    block.y = (i32)pos1.y;

    i32 dz = glm::sign(pos2.z - pos1.z);
    if(dz != 0){
        deltaZ = glm::min(dz / (pos2.z - pos1.z), 10000000.0f);
    }else{
        deltaZ = 10000000.0f;
    }
    if(dz > 0){
        maxZ = deltaZ * (1.0f - glm::fract(pos1.z));
    }else{
        maxZ = deltaZ * glm::fract(pos1.z);
    } 
    block.z = (i32)pos1.z;

    while (true)
    {
        if (maxX < maxY) {
            if (maxX < maxZ) {
                block.x += dx;
                maxX += deltaX;
                stepDir = 0;
            } else {
                block.z += dz;
                maxZ += deltaZ;
                stepDir = 2;
            }
        } 
        else {
            if (maxY < maxZ) {
                block.y += dy;
                maxY += deltaY;
                stepDir = 1;
            } else {
                block.z += dz;
                maxZ += deltaZ;
                stepDir = 2;
            }
        }
        if (maxX > 1 && maxY > 1 && maxZ > 1){
            isSolid = false;
            break;
        }

        if(world->IsWithinWorld(block.x, block.y, block.z)){        
            if(world->ContainsBlock(block.x, block.y, block.z)){
                isSolid = true;
                
                if(stepDir == 0){
                    blockNormal.x = -dx;
                }
                else if(stepDir == 1){
                    blockNormal.y = -dy;
                }
                else{
                    blockNormal.z = -dz;
                } 
            
                break;
            }
            else{
                isSolid = false;
            }
        }
        else{
            isSolid = false;
        }
    }
}


glm::ivec3 BlockHandler::GetBlock(){
    return block;
}

bool BlockHandler::IsSolid(){
    return isSolid;
}