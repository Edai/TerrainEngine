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


private:
    void ChangePitch(float);
    void ChangeHeading(float);

    bool move_camera;

    glm::mat4 projectMatrix;
    glm::mat4 viewMatrix;

    float tolerate;
    float speed;
    double aspect;
    double fov;
    float scale;
    float heading;
    float pitch;
    float max_pitch;
    float max_heading;

    glm::vec3 position;
    glm::vec3 posDelta;
    glm::vec3 lookAt;
    glm::vec3 dir;
    glm::vec3 mouse_position;
};


#endif //TERRAINENGINE_CAMERA_HPP
