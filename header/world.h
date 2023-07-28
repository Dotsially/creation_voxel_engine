#pragma once
#include "depedencies.h"
#include "chunk.h"

#define REGION_SIZE 12

class World{
    Chunk* chunks;

public:
    World();
    ~World();

    void Draw();
    void AddBlock(i32 x, i32 y, i32 z);
    void RemoveBlock(i32 x, i32 y, i32 z);
    bool IsWithinWorld(i32 x, i32 y, i32 z);
    bool ContainsBlock(i32 x, i32 y, i32 z);
    bool NeighborIsAira(i32 x, i32 y, i32 z);
    void GetNeighbors(Chunk* neighbors[4], i32 x, i32 z);
};  