#pragma once
#include "depedencies.h"
#include "FastNoiseLite.h"
#include "vertices_list.h"
#include <vector>
#include "mesh.h"
#include "tile.h"

#define CHUNK_SIZE 32

class Chunk{
    glm::vec2 position;
    u16 chunkData[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
    std::vector<f32> chunkMeshVertices;
    std::vector<u32> chunkMeshIndices;
    u32 indicesCount;
    Mesh chunkMesh;
    bool firstMesh = true;
    Chunk* chunkNeighbors[4];

    void AddFace(u32 faceIndex, glm::vec2 voxelIndex, glm::vec3);
public:
    Chunk();
    ~Chunk();
    void CreateChunkData(fnl_state* noise, i32 x, i32 z); 
    void CreateChunkMesh(Chunk** chunks);
    void SendMeshData();
    void Draw();
    void AddBlock(Chunk** chunks, i32 x, i32 y, i32 z, u16 blockID);
    void RemoveBlock(Chunk** chunks, i32 x, i32 y, i32 z);
    u32 GetChunkMeshSize();
    u32 GetChunkIndicesSize();
    f32* GetChunkMeshData();
    u32* GetChunkIndicesData();
    bool ConstainsBlock(i32 x, i32 y, i32 z);
    bool IsWithinChunk(i32 x, i32 y, i32 z);
    glm::vec2 GetPosition();
};