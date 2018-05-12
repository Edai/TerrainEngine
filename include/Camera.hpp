//
// Created by edai on 12/05/18.
//

#ifndef TERRAINENGINE_CAMERA_HPP
#define TERRAINENGINE_CAMERA_HPP

#include <Application.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera();
    ~Camera() = default;

    enum CameraDirection
    {
        LEFT, RIGHT, FORWARD, BACK
    };

    void SetPosition(glm::vec3);
    void SetLookAt(glm::vec3);
    void SetViewport(double, double);
    void SetPos(int, int, int, int);
    void Update();
    void Move(CameraDirection);
    void Rotate(int, int);

    glm::mat4 ProjectionMatrix;
    glm::mat4 ViewMatrix;
    glm::mat4 ModelMatrix;
private:
    void ChangePitch(float);
    void ChangeHeading(float);

    float tolerate;
    float speed;
    double aspect;
    double fov;
    float scale;
    float heading;
    float pitch;
    float max_pitch;
    float max_heading;
    bool move_camera;

    glm::vec3 camera_position;
    glm::vec3 camera_position_delta;
    glm::vec3 camera_look_at;
    glm::vec3 camera_direction;
    glm::vec3 mouse_position;
};


#endif //TERRAINENGINE_CAMERA_HPP
