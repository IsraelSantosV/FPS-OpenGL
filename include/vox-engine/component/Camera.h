//
// Created by Israel on 05/04/2022.
//

#ifndef VOXENGINE_CAMERA_H
#define VOXENGINE_CAMERA_H

#include "vox-engine/resources/Math.h"
#include "vox-engine/system/Entity.h"

enum CameraType {
    ORTHO, FREE
};

enum CameraDirection {
    UP, DOWN, LEFT, RIGHT, FORWARD, BACK
};

class Camera : public Behaviour {
public:
    void init() override;

    void reset();
    //This function updates the camera
    //Depending on the current camera mode, the projection and viewport matrices are computed
    //Then the position and location of the camera is updated
    void Update() override;

    //Given a specific moving direction, the camera will be moved in the appropriate direction
    //For a spherical camera this will be around the look_at point
    //For a free camera a delta will be computed for the direction of movement.
    void move(CameraDirection dir);
    //Change the pitch (up, down) for the free camera
    void changePitch(float degrees);
    //Change heading (left, right) for the free camera
    void changeHeading(float degrees);

    //Change the heading and pitch of the camera based on the 2d movement of the mouse
    void move2D(int x, int y);

    //Setting Functions
    //Changes the camera mode, only three valid modes, Ortho, Free, and Spherical
    void setMode(CameraType cam_mode);
    //Set's the look at point for the camera
    void setLookAt(vec3 pos);
    //Changes the Field of View (FOV) for the camera
    void setFOV(double fov);
    //Change the viewport location and size
    void setViewport(int loc_x, int loc_y, int width, int height);
    //Change the clipping distance for the camera
    void setClipping(double near_clip_distance, double far_clip_distance);

    void setDistance(double cam_dist);
    void setMouseInput(int button, int state, int x, int y);

    //Getting Functions
    CameraType getMode();
    void getViewport(int &loc_x, int &loc_y, int &width, int &height);
    void getMatrices(mat4 &P, mat4 &V, mat4 &M);

    CameraType camera_mode;
    static Camera* main;
    static bool useDefaultCameraController;

    int viewport_x;
    int viewport_y;

    int window_width;
    int window_height;

    double aspect;
    double field_of_view;
    double near_clip;
    double far_clip;

    float camera_scale;
    float camera_heading;
    float camera_pitch;

    float max_pitch_rate;
    float max_heading_rate;
    float sensibility;
    bool move_camera;

    vec3 camera_position_delta;
    vec3 camera_look_at;
    vec3 camera_direction;

    vec3 camera_up;
    vec3 mouse_position;

    mat4 projection;
    mat4 view;
    mat4 model;
    mat4 MVP;
};


#endif //VOXENGINE_CAMERA_H
