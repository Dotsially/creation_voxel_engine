#pragma once
#include "depedencies.h"
#include "FastNoiseLite.h"
#include "vertices_list.h"
#include "glm/glm.hpp"
#include <vector>
#include "mesh.h"

#define CHUNK_SIZE 32

class Chunk{
    u16 chunkData[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    std::vector<f32> chunkMeshVertices;
    std::vector<u32> chunkMeshIndices;
    u32 indicesCount;
    Mesh chunkMesh;

    void AddFace(u32 faceIndex, glm::vec3);
public:
    Chunk();
    ~Chunk();
    void CreateChunkData(); 
    void CreateChunkMesh();
    void Draw();
    void AddBlock(int x, int y, int z);
    void RemoveBlock(int x, int y, int z);
    u32 GetChunkMeshSize();
    u32 GetChunkIndicesSize();
    f32* GetChunkMeshData();
    u32* GetChunkIndicesData();
    bool ConstainsBlock(int x, int y, int z);
    bool IsWithinChunk(int x, int y, int z);
};