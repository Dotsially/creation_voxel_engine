#include "entity_mesh.h"
#include "iostream"

EntityMesh::EntityMesh(){
    mesh = Mesh();

    for(i32 i = 0; i < 4; i++){
        vertices.push_back(VerticesList::verticesEntity1x1[0+(i*4)]);
        
        vertices.push_back(VerticesList::verticesEntity1x1[1+(i*4)]);
    }

    for(u32 i : VerticesList::indicesEntity){
                indices.push_back(i);
    }


    mesh.InitializeMesh(GL_STATIC_DRAW, vertices.data(), vertices.size(), indices.data(), indices.size());

}

EntityMesh::~EntityMesh(){

}

void EntityMesh::Update(glm::vec3 position){

    for(i32 i = 0; i < 4; i++){
        vertices.push_back(VerticesList::verticesEntity1x1[0+(i*2)] + position.x);
        
        vertices.push_back(VerticesList::verticesEntity1x1[1+(i*2)] + position.y);
    }

    for(u32 i : VerticesList::indicesEntity){
                indices.push_back(i);
    }

    mesh.SendChunkData(vertices.data(), vertices.size(), indices.data(), indices.size());

}

void EntityMesh::Draw(glm::vec3 position){
    transform = glm::translate(glm::mat4(1.0f), position+1.0f);
    transform = glm::scale(transform, glm::vec3(1,2,1));
    mesh.DrawMesh(indices.size(), transform);
}