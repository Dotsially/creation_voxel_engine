#pragma once
#include "depedencies.h"
#include "glm/glm.hpp"

typedef struct Tile{
    u16 tileID;
    u16 tileType;
    glm::vec2 top;
    glm::vec2 bottom;
    glm::vec2 left;
    glm::vec2 right;
    glm::vec2 front;
    glm::vec2 back;
}Tile;

const Tile air = {};

const Tile grass = {
    1, //tileID
    0, //tileType 
    glm::vec2(2,12), //top
    glm::vec2(1,13), //bottom
    glm::vec2(1,12), //left
    glm::vec2(1,12), //right
    glm::vec2(1,12), //front
    glm::vec2(1,12), //back
};

const Tile dirt = {
    2, //tileID
    0, //tileType 
    glm::vec2(1,13), //top
    glm::vec2(1,13), //bottom
    glm::vec2(1,13), //left
    glm::vec2(1,13), //right
    glm::vec2(1,13), //front
    glm::vec2(1,13), //back
};

const Tile stone = {
    3, //tileID
    0, //tileType 
    glm::vec2(0, 14), //top
    glm::vec2(0, 14), //bottom
    glm::vec2(0, 14), //left
    glm::vec2(0, 14), //right
    glm::vec2(0, 14), //front
    glm::vec2(0, 14), //back
};

const Tile tiles[8] = {air, grass, dirt, stone, air, air, air, air};