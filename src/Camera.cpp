//
// Created by edai on 12/05/18.
//

#include <Skybox.hpp>
#include "Camera.hpp"

Camera::Camera() : speed(0.025f), fov(45.0), scale(0.5f), max_pitch(5), max_heading(5),
                   move_camera(false), camera_position_delta(glm::vec3(0, 0, 0)), tolerate(2.0f)
{
}

void Camera::Update()
{
    glm::quat pitchQ, headingQ;

    camera_direction = glm::normalize(camera_look_at - camera_position);
    pitchQ = glm::angleAxis(pitch, glm::cross(camera_direction, glm::vec3(0, 1, 0)));
    headingQ = glm::angleAxis(heading, glm::vec3(0, 1, 0));
    camera_direction = glm::rotate(glm::normalize(glm::cross(pitchQ, headingQ)), camera_direction);
    if (- Skybox::size / 2 < (camera_position + camera_position_delta).x - tolerate &&
        Skybox::size / 2 > (camera_position + camera_position_delta).x + tolerate &&
        - Skybox::size / 2 < (camera_position + camera_position_delta).z - tolerate &&
        Skybox::size / 2 > (camera_position + camera_position_delta).z + tolerate&&
        - Skybox::size / Skybox::factorY < (camera_position + camera_position_delta).y  - tolerate &&
        Skybox::size / Skybox::factorY > (camera_position + camera_position_delta).y + tolerate)
        camera_position += camera_position_delta * 2.0f;
    camera_look_at = camera_position + camera_direction * speed;
    camera_position_delta = camera_position_delta * speed;
    heading *= speed;
    pitch *= speed;

    ProjectionMatrix = glm::perspective(fov, aspect, 1.0, 5000.0);
    ViewMatrix = glm::lookAt(camera_position, camera_look_at, glm::vec3(0, 1, 0));
    ModelMatrix = glm::mat4(1.0f);
}

void Camera::SetPosition(glm::vec3 pos)
{
    camera_position = pos;
}

void Camera::SetLookAt(glm::vec3 pos)
{
    camera_look_at = pos;
}

void Camera::Move(CameraDirection dir)
{
    switch (dir)
    {
        case LEFT:
            camera_position_delta -= glm::cross(camera_direction, glm::vec3(0, 1, 0)) * scale;
            break;
        case RIGHT:
            camera_position_delta += glm::cross(camera_direction, glm::vec3(0, 1, 0)) * scale;
            break;
        case FORWARD:
            camera_position_delta += camera_direction * scale;
            break;
        case BACK:
            camera_position_delta -= camera_direction * scale;
            break;
    }
}
void Camera::ChangePitch(float d)
{
    if (d < -max_pitch)
        d = -max_pitch;
    else if (d > max_pitch)
        d = max_pitch;
    pitch += d;

    if (pitch > 360.0f)
        pitch -= 360.0f;
    else if (pitch < -360.0f)
        pitch += 360.0f;
}

void Camera::ChangeHeading(float d)
{
    if (d < -max_heading)
        d = -max_heading;
    else if (d > max_heading)
        d = max_heading;
    if (pitch > 90 && pitch < 270 || (pitch < -90 && pitch > -270))
        heading -= d;
    else
        heading += d;
    if (heading > 360.0f)
        heading -= 360.0f;
    else if (heading < -360.0f)
        heading += 360.0f;
}
void Camera::Rotate(int x, int y)
{
    glm::vec3 mouse_delta = mouse_position - glm::vec3(x, y, 0);
    if (move_camera)
    {
        ChangeHeading(speed * mouse_delta.x);
        ChangePitch(speed * mouse_delta.y);
    }
    mouse_position = glm::vec3(x, y, 0);
}

void Camera::SetPos(int button, int state, int x, int y)
{
    move_camera = button == GLUT_LEFT_BUTTON && state == GLUT_DOWN;
    mouse_position = glm::vec3(x, y, 0);
}

void Camera::SetViewport(double width, double height)
{
    aspect = width / height;
}