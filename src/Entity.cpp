#include "entity.h"


Entity::Entity(glm::vec3 position){
    this->position = position;
}

Entity::~Entity(){


}

void Entity::Update(){
    if(vars.playerControlled >= 1){
        const u8* keystate = SDL_GetKeyboardState(NULL);

        if(keystate[SDL_SCANCODE_W]){
            this->position.z += 1;
        }

        
        if(keystate[SDL_SCANCODE_S]){
            this->position.z -= 1;
        }

        
        if(keystate[SDL_SCANCODE_A]){
            this->position.x += 1;
        }

        
        if(keystate[SDL_SCANCODE_D]){
            this->position.x -= 1;
        }
    }

}

glm::vec3 Entity::GetPosition(){
    return position;
}

void Entity::MoveNorth(){

}



void Entity::MoveSouth(){
    
}


void Entity::MoveEast(){
    
}



void Entity::MoveWest(){
    
}


void Entity::MoveNorthEast(){
    
}


void Entity::MoveNorthWest(){
    
}


void Entity::MoveSouthEast(){
    
}


void Entity::MoveSouthWest(){
    
}