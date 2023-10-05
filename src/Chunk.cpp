#include "chunk.h"
#include <iostream>

Chunk::Chunk(){
}

Chunk::~Chunk(){

}


void Chunk::CreateChunkData(fnl_state* noise, i32 x, i32 z){
    position = glm::vec2(x,z);


    for(i32 x = 0; x < CHUNK_SIZE; x++){
        for(i32 z = 0; z < CHUNK_SIZE; z++){
            i32 value = (fnlGetNoise2D(noise, x + (position.x*CHUNK_SIZE), z + (position.y*CHUNK_SIZE))+1)*8;
            for(i32 y = 0; y < CHUNK_SIZE; y++){
                if(y == value){
                    chunkData[x][y][z] = 1;
                }
                else if(y < value && y > value-2){
                    chunkData[x][y][z] = 2;
                }
                else if(y <= value-2 || y == 0){
                    chunkData[x][y][z] = 3;
                }
                else{
                    chunkData[x][y][z] = 0;
                }
            }
        }
    }
}

void Chunk::CreateChunkMesh(Chunk** chunks){
    indicesCount = 0;
    chunkMeshVertices.clear();
    chunkMeshIndices.clear();
    for(i32 x = 0; x < CHUNK_SIZE; x++){
        for(i32 y = 0; y < CHUNK_SIZE; y++){
            for(i32 z = 0; z < CHUNK_SIZE; z++){
                if(chunkData[x][y][z] != 0){
                if(z - 1 < 0){
                    if(chunks[0] != nullptr){
                        if(chunks[0]->chunkData[x][y][CHUNK_SIZE-1] == 0){
                            AddFace(0, tiles[chunkData[x][y][z]].front, glm::vec3(x,y,z));
                        }    
                    }else{
                        AddFace(0, tiles[chunkData[x][y][z]].front, glm::vec3(x,y,z));
                    }
                }
                else if(chunkData[x][y][z-1] == 0){
                    AddFace(0, tiles[chunkData[x][y][z]].front, glm::vec3(x,y,z));
                }
                if(z + 1 >= CHUNK_SIZE){
                    if(chunks[1] != nullptr){
                        if(chunks[1]->chunkData[x][y][0] == 0){
                            AddFace(1, tiles[chunkData[x][y][z]].back, glm::vec3(x,y,z));
                        }    
                    }else{
                        AddFace(1, tiles[chunkData[x][y][z]].back, glm::vec3(x,y,z));
                    }
                }
                else if(chunkData[x][y][z+1] == 0){
                    AddFace(1, tiles[chunkData[x][y][z]].back, glm::vec3(x,y,z));
                }

                if(x - 1 < 0){
                    if(chunks[2] != nullptr){
                        if(chunks[2]->chunkData[CHUNK_SIZE-1][y][z] == 0){
                            AddFace(2, tiles[chunkData[x][y][z]].left, glm::vec3(x,y,z));
                        }    
                    }else{
                        AddFace(2, tiles[chunkData[x][y][z]].left, glm::vec3(x,y,z));
                    }
                }
                else if(chunkData[x-1][y][z] == 0){
                    AddFace(2, tiles[chunkData[x][y][z]].left, glm::vec3(x,y,z));
                }
                if(x + 1 >= CHUNK_SIZE){
                    if(chunks[3] != nullptr){
                        if(chunks[3]->chunkData[0][y][z] == 0){
                            AddFace(3, tiles[chunkData[x][y][z]].right, glm::vec3(x,y,z));
                        }    
                    }else{
                        AddFace(3, tiles[chunkData[x][y][z]].right, glm::vec3(x,y,z));
                    }
                }
                else if(chunkData[x+1][y][z] == 0){
                    AddFace(3, tiles[chunkData[x][y][z]].right, glm::vec3(x,y,z));
                }

                if(y - 1 < 0){
                    AddFace(5, tiles[chunkData[x][y][z]].bottom, glm::vec3(x,y,z));
                }
                else if(chunkData[x][y-1][z] == 0){
                    AddFace(5, tiles[chunkData[x][y][z]].bottom, glm::vec3(x,y,z));
                }
                if(y + 1 > 31){
                    AddFace(4, tiles[chunkData[x][y][z]].top, glm::vec3(x,y,z));
                }
                else if(chunkData[x][y+1][z] == 0){
                    AddFace(4, tiles[chunkData[x][y][z]].top, glm::vec3(x,y,z));
                }
                }
            }
        }
    }
    
    if(firstMesh){
        chunkMesh.InitializeChunkMesh(GL_DYNAMIC_DRAW, GetChunkMeshData(), GetChunkMeshSize(), GetChunkIndicesData(), GetChunkIndicesSize());
        firstMesh = false;
    }
}

void Chunk::AddFace(u32 faceIndex, glm::vec2 voxelIndex, glm::vec3 position){
    for(i32 i = 0; i < 4; i++){
        chunkMeshVertices.push_back(VerticesList::verticesCube[faceIndex][0 +(i*3)] + position.x);
        
        chunkMeshVertices.push_back(VerticesList::verticesCube[faceIndex][1+(i*3)] + position.y);
        
        chunkMeshVertices.push_back(VerticesList::verticesCube[faceIndex][2+(i*3)] + position.z);
        
        chunkMeshVertices.push_back(i);
        chunkMeshVertices.push_back(faceIndex);
        chunkMeshVertices.push_back(voxelIndex.x);
        chunkMeshVertices.push_back(voxelIndex.y);
    }

    if(faceIndex % 2 == 0){
        for(u32 i : VerticesList::indicesCube[0]){
                chunkMeshIndices.push_back(i + (indicesCount*4));
        }
    }else{
        for(u32 i : VerticesList::indicesCube[1]){
                chunkMeshIndices.push_back(i + (indicesCount*4));
        }
    }
    indicesCount++;
}

f32* Chunk::GetChunkMeshData(){
    return chunkMeshVertices.data();
}

bool Chunk::ConstainsBlock(i32 x, i32 y, i32 z){
    return chunkData[x][y][z] ? true : false;
}
bool Chunk::IsWithinChunk(i32 x, i32 y, i32 z){
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

void Chunk::AddBlock(Chunk** chunks, i32 x, i32 y, i32 z, u16 blockID){
    if(IsWithinChunk(x,y,z) && chunkData[x][y][z] == 0){
        chunkData[x][y][z] = blockID;
        CreateChunkMesh(chunks);
        SendMeshData();
    }
}

void Chunk::RemoveBlock(Chunk** chunks, i32 x, i32 y, i32 z){
    if(IsWithinChunk(x,y,z) && chunkData[x][y][z] > 0){
        chunkData[x][y][z] = 0;
        CreateChunkMesh(chunks);
        SendMeshData();
    }
}

void Chunk::Draw(){
    chunkMesh.DrawChunk(GetChunkIndicesSize(), glm::vec3(position.x*CHUNK_SIZE+0.5, 0.5, position.y*CHUNK_SIZE+0.5));
}


void Chunk::SendMeshData(){
    chunkMesh.SendChunkData(GetChunkMeshData(), GetChunkMeshSize(), GetChunkIndicesData(), GetChunkIndicesSize());
}

glm::vec2 Chunk::GetPosition(){
    return position;
}