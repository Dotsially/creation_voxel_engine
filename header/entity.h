#pragma once
#include "depedencies.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"

typedef struct entityVariables{
    i32 modelType;
    u8 walkable;
    u8 playerControlled;
    u8 item;
    u8 pickup;
}entityVariables;

class Entity{
    glm::vec3 position;    

public:
    Entity(glm::vec3 position);
    ~Entity();
    void Update();
    void Draw();
    glm::vec3 GetPosition();
    entityVariables vars;


    //Entity movement functions
    void MoveNorth();
    void MoveSouth();
    void MoveEast();
    void MoveWest();
    void MoveNorthEast();
    void MoveNorthWest();
    void MoveSouthEast();
    void MoveSouthWest();
};