#include "camera.h"


Camera::Camera(CameraType type, glm::vec3 position){
    this->cameraType = type;
    switch(cameraType){
        case CAMERA_FREECAM:
        case CAMERA_FIRSTPERSON:
            this->position = position;
            this->target = glm::vec3{0.0f,0.0f,-1.0f};
            this->worldUp = glm::vec3{0.0f,1.0f,0.0f};
            this->right = glm::normalize(glm::cross(this->target, this->worldUp));
            this->up = glm::normalize(glm::cross(this->right, this->target));
            this->fov = glm::radians(80.0);
            this->yaw = -90.0f;
            this->moveDirection = glm::normalize(
                glm::vec3{glm::cos(glm::radians(this->yaw)), 0.0, glm::sin(glm::radians(this->yaw))});
            break;
        case CAMERA_THIRDPERSON:
            //TODO
            break; 
    }
}

Camera::~Camera(){
    
}


void Camera::Update(const u8* keystate){    
    if(cameraType == CAMERA_FREECAM){
        if (keystate[SDL_SCANCODE_W]){
            position += 0.2f * moveDirection;
        }
        if (keystate[SDL_SCANCODE_S]){
            position -= 0.2f * moveDirection;
        }
        if (keystate[SDL_SCANCODE_A]){
            position -= 0.2f * right;
        }
        if (keystate[SDL_SCANCODE_D]){
            position += 0.2f * right;
        }
        if(keystate[SDL_SCANCODE_SPACE]){
            position.y += 0.2f;
        }
        if(keystate[SDL_SCANCODE_LSHIFT]){
            position.y -= 0.2f;
        }
    }

    int x;
    int y;
    SDL_GetRelativeMouseState(&x,&y);

    if(cameraType == CAMERA_FREECAM || cameraType == CAMERA_FIRSTPERSON){
        yaw += (f32)x * 0.2f;
        pitch -= (f32)y* 0.2f;     
        
        if (pitch > 89.0f){
            pitch = 89.0f;
        }
        if (pitch < -89.0f){
            pitch = -89.0f;
        }
    
        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        
        target = glm::normalize(direction);
    
        right = glm::normalize(glm::cross(target, glm::vec3(0,1,0)));
    
        up =  glm::normalize(glm::cross(right, target));
    
        moveDirection =  glm::normalize(glm::vec3(cos(glm::radians(yaw)), 0, sin(glm::radians(yaw))));
    } 
}        


glm::mat4 Camera::GetViewMatrix(){
    return glm::lookAt(this->position, this->position + this->target, this->up);
}

glm::mat4 Camera::GetProjectMatrix(){
    return glm::perspective(this->fov, 1280.0f/720.0f, 0.1f, 1000.0f);
}


glm::vec3 Camera::GetPosition(){
    return position;
}

glm::vec3 Camera::GetTarget(){
    return target;
}