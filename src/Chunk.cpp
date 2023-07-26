#include "chunk.h"
#include <iostream>

Chunk::Chunk(): chunkMesh(GL_DYNAMIC_DRAW){
}

Chunk::~Chunk(){

}


void Chunk::CreateChunkData(){
    fnl_state noise = fnlCreateState();
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    noise.frequency = 0.01f;
    noise.lacunarity = 2.0f;
    noise.gain = 0.5f;

    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int z = 0; z < CHUNK_SIZE; z++){
            int value = (fnlGetNoise2D(&noise, x, z)+1)*8;
            for(int y = 0; y < CHUNK_SIZE; y++){
                if(y < value || y == 0){
                    chunkData[x][y][z] = 1;
                }
                else{
                    chunkData[x][y][z] = 0;
                }
            }
        }
    }
}

void Chunk::CreateChunkMesh(){
    indicesCount = 0;
    chunkMeshVertices.clear();
    chunkMeshIndices.clear();
    for(int x = 0; x < CHUNK_SIZE; x++){
        for(int y = 0; y < CHUNK_SIZE; y++){
            for(int z = 0; z < CHUNK_SIZE; z++){
                if(chunkData[x][y][z] != 0){
                if(z - 1 < 0){
                    AddFace(0, glm::vec3(x,y,z));
                }
                else if(chunkData[x][y][z-1] == 0){
                    AddFace(0, glm::vec3(x,y,z));
                }
                if(z + 1 > 31){
                    AddFace(1, glm::vec3(x,y,z));
                }
                else if(chunkData[x][y][z+1] == 0){
                    AddFace(1, glm::vec3(x,y,z));
                }

                if(x - 1 < 0){
                    AddFace(2, glm::vec3(x,y,z));
                }
                else if(chunkData[x-1][y][z] == 0){
                    AddFace(2, glm::vec3(x,y,z));
                }
                if(x + 1 > 31){
                    AddFace(3, glm::vec3(x,y,z));
                }
                else if(chunkData[x+1][y][z] == 0){
                    AddFace(3, glm::vec3(x,y,z));
                }

                if(y - 1 < 0){
                    AddFace(4, glm::vec3(x,y,z));
                }
                else if(chunkData[x][y-1][z] == 0){
                    AddFace(4, glm::vec3(x,y,z));
                }
                if(y + 1 > 31){
                    AddFace(5, glm::vec3(x,y,z));
                }
                else if(chunkData[x][y+1][z] == 0){
                    AddFace(5, glm::vec3(x,y,z));
                }
                }
            }
        }
    }
    chunkMesh.InitializeMesh(GetChunkMeshData(), GetChunkMeshSize(), GetChunkIndicesData(), GetChunkIndicesSize());
}

void Chunk::AddFace(u32 faceIndex, glm::vec3 position){
    for(int i = 0; i < 4; i++){
        chunkMeshVertices.push_back(VerticesList::verticesCube[faceIndex][0 +(i*3)] + position.x);
        
        chunkMeshVertices.push_back(VerticesList::verticesCube[faceIndex][1+(i*3)] + position.y);
        
        chunkMeshVertices.push_back(VerticesList::verticesCube[faceIndex][2+(i*3)] + position.z);
    }

    for(u32 i : VerticesList::indicesCube){
            chunkMeshIndices.push_back(i + (indicesCount*4));
    }
    indicesCount++;
}

f32* Chunk::GetChunkMeshData(){
    return chunkMeshVertices.data();
}

bool Chunk::ConstainsBlock(int x, int y, int z){
    return chunkData[x][y][z] ? true : false;
}
bool Chunk::IsWithinChunk(int x, int y, int z){
    if(x >= 0 && x < 32 && y >= 0 && y < 32 && z >= 0 && z < 32){
        return true;
    }
    return false;
}

u32* Chunk::GetChunkIndicesData(){
    return chunkMeshIndices.data();
}

u32 Chunk::GetChunkMeshSize(){
    return chunkMeshVertices.size();
}

u32 Chunk::GetChunkIndicesSize(){
    return chunkMeshIndices.size();
}

void Chunk::AddBlock(int x, int y, int z){
    if(IsWithinChunk(x,y,z)){
        chunkData[x][y][z] = 1;
        CreateChunkMesh();
        chunkMesh.SendData(GetChunkMeshData(), GetChunkMeshSize(), GetChunkIndicesData(), GetChunkIndicesSize());
    }
}

void Chunk::RemoveBlock(int x, int y, int z){
    if(IsWithinChunk(x,y,z)){
        chunkData[x][y][z] = 0;
        CreateChunkMesh();
        chunkMesh.SendData(GetChunkMeshData(), GetChunkMeshSize(), GetChunkIndicesData(), GetChunkIndicesSize());
    }
}

void Chunk::Draw(){
    chunkMesh.Draw(GetChunkIndicesSize());
}