//
// Created by aluno on 09/03/2022.
//

#ifndef OPENGL_CAMERA_CAMERA_H
#define OPENGL_CAMERA_CAMERA_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

static struct Camera_Movement {
    bool forward = false;
    bool backward = false;
    bool left = false;
    bool right = false;
};

//Default values
constexpr float YAW = -45.0f;
constexpr float PITCH = 0;
constexpr float SPEED = 0.008f;
constexpr float SENSITIVITY = 0.04f;
constexpr float ZOOM = 35.0f;
constexpr float CAM_START[3] = { -9.0f, 0.5f, 8.7f };
constexpr float JUMP_HEIGHT = CAM_START[1] + 0.5f;
constexpr float BOUNDRY_SIZE = 9.6;
constexpr float MAX_LOOK_ANGLE = 19.0f;
constexpr float TIME_BETWEEN_FOOTSTEPS = 290.0f;

//Abstract camera class for process input and
//calculates the corresponding Euler angles
class Camera {
private:
    void updateCameraVectors(){
        glm::vec3 front;
        front.x = cos(glm::radians(YAW)) * cos(glm::radians(PITCH));
        front.y = sin(glm::radians(PITCH));
        front.z = sin(glm::radians(YAW)) * cos(glm::radians(PITCH));
        Front = glm::normalize(front);

        //Normalize the vectors, because their length gets
        //closer to 0 the more you look up or down which results
        //in slower movement
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
public:
    Camera_Movement CamMove;
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    //Euler angles
    float Yaw;
    float Pitch;

    //Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    bool OnGround;
    bool IsFalling;

    //Constructor with vectors - default constructor
    Camera(glm::vec3 position = glm::vec3(CAM_START[0], CAM_START[1], CAM_START[2]),
           glm::vec3 up = glm::vec3(0, 1, 0), float yaw = YAW, float pitch = PITCH){
        Front = glm::vec3(0,0, -1);
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Zoom = ZOOM;

        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        OnGround = true;
        IsFalling = false;
        updateCameraVectors();
    }

    //Constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
           float yaw, float pitch){
        Front = glm::vec3(0,0,-1);
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Zoom = ZOOM;

        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    //Returns the view matrix calculated using euler angles and the look at matrix
    glm::mat4 getViewMatrix(){
        return glm::lookAt(Position, Position + Front, Up);
    }

    //Process input received keyboard
    void processKeyboard(float deltaTime){
        int posX = Position.x;
        int posY = Position.y;
        int posZ = Position.z;

        float velocity = MovementSpeed * deltaTime;
        if(CamMove.forward){
            Position += Front * velocity;
        }
        if(CamMove.backward){
            Position -= Front * velocity;
        }
        if(CamMove.left){
            Position -= Right * velocity;
        }
        if(CamMove.right){
            Position += Right * velocity;
        }

        if(Position.x < -BOUNDRY_SIZE){ //Left Wall green Wall Broundries
            if(CamMove.forward){
                Position -= Front * velocity;
            }
            if(CamMove.backward){
                Position += Front * velocity;
            }
            if(CamMove.left){
                Position += Right * velocity;
            }
            if(CamMove.right){
                Position -= Right * velocity;
            }
        }
        if(Position.x > BOUNDRY_SIZE){ //Right Wall
            if(CamMove.forward){
                Position -= Front * velocity;
            }
            if(CamMove.backward){
                Position += Front * velocity;
            }
            if(CamMove.left){
                Position += Right * velocity;
            }
            if(CamMove.right){
                Position -= Right * velocity;
            }
        }
        if(Position.z > -BOUNDRY_SIZE){ //Right Wall
            if(CamMove.forward){
                Position -= Front * velocity;
            }
            if(CamMove.backward){
                Position += Front * velocity;
            }
            if(CamMove.left){
                Position += Right * velocity;
            }
            if(CamMove.right){
                Position -= Right * velocity;
            }
        }
        if(Position.z > BOUNDRY_SIZE){ //Right Wall
            if(CamMove.forward){
                Position -= Front * velocity;
            }
            if(CamMove.backward){
                Position += Front * velocity;
            }
            if(CamMove.left){
                Position += Right * velocity;
            }
            if(CamMove.right){
                Position -= Right * velocity;
            }
        }

        if(OnGround){
            Position.y = CAM_START[1];
        }
        else if(!IsFalling){
            //Rising
        }
        else{
            //Falling
        }

        updateCameraVetors();
    }

    void jump(int deltaTime){
        if(OnGround){
            IsFalling = false;
            OnGround = false;
            updateCameraVectors();
        }
    }

    void processMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true){
        xOffset *= MouseSensitivity;
        yOffset *= MouseSensitivity;

        Yaw += xOffset;
        Pitch += yOffset;

        if(constrainPitch){
            if(Pitch > MAX_LOOK_ANGLE){
                Pitch = MAX_LOOK_ANGLE;
            }
            if(Pitch < -MAX_LOOK_ANGLE){
                Pitch = -MAX_LOOK_ANGLE;
            }
        }
    }

    void rise(){
        if(Position.y <= JUMP_HEIGHT){
            Position.y += 0.06;
        }
        else{
            IsFalling = true;
        }
    }

    void fall(){
        if(Position.y <= 0.503f){
            Position.y = CAM_START[1];
            OnGround = true;
        }
        else{
            Position.y -= 0.05f;
        }

        updateCameraVectors();
    }

    void processMouseScroll(float yOffset){
        if(Zoom >= 1 && Zoom <= 45.0){
            Zoom -= yOffset;
        }
        if(Zoom <= 1){
            Zoom = 1;
        }
        if(Zoom >= 45.0){
            Zoom = 45.0;
        }
    }

    void reset(){
        Position = glm::vec3(CAM_START[0], CAM_START[1], CAM_START[2]);
        WorldUp = glm::vec3(0, 1, 0);
        Yaw = YAW;
        Pitch = PITCH;
        Front = glm::vec3(0, 0, -1);
        MovementSpeed = SPEED;
        MouseSensitivity = SENSITIVITY;
        Zoom = ZOOM;
        updateCameraVectors();
    }
};


#endif //OPENGL_CAMERA_CAMERA_H
