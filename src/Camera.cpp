//
// Created by edai on 12/05/18.
//

#include <Skybox.hpp>

Camera::Camera() : speed(0.025f), fov(45.0), scale(0.5f), max_pitch(5), max_heading(5),
                   move_camera(false), posDelta(glm::vec3(0, 0, 0)), tolerate(2.0f)
{
}

void Camera::Update()
{
    static glm::quat pitchQ, headingQ;

    dir = glm::normalize(lookAt - position);
    pitchQ = glm::angleAxis(pitch, glm::cross(dir, glm::vec3(0, 1, 0)));
    headingQ = glm::angleAxis(heading, glm::vec3(0, 1, 0));
    dir = glm::rotate(glm::normalize(glm::cross(pitchQ, headingQ)), dir);

    if (- Skybox::size / 2 < (position + posDelta).x - tolerate &&
        Skybox::size / 2 > (position + posDelta).x + tolerate &&
        - Skybox::size / 2 < (position + posDelta).z - tolerate &&
        Skybox::size / 2 > (position + posDelta).z + tolerate&&
        - Skybox::size / Skybox::factorY < (position + posDelta).y  - tolerate &&
        Skybox::size / Skybox::factorY > (position + posDelta).y + tolerate)
        position += posDelta * 2.0f;
    lookAt = position + dir * speed;
    posDelta = posDelta * speed;
    heading *= speed;
    pitch *= speed;

    projectMatrix = glm::perspective(fov, aspect, 1.0, 5000.0);
    viewMatrix = glm::lookAt(position, lookAt, glm::vec3(0, 1, 0));

    glm::mat4 mvp = projectMatrix * viewMatrix;
    glLoadMatrixf(glm::value_ptr(mvp));
}

void Camera::SetPosition(glm::vec3 pos)
{
    position = pos;
}

void Camera::SetLookAt(glm::vec3 pos)
{
    lookAt = pos;
}

void Camera::Move(CameraDirection d)
{
    switch (d)
    {
        case FORWARD:
            posDelta += dir * scale;
            break;
        case BACK:
            posDelta -= dir * scale;
            break;
        case LEFT:
            posDelta -= glm::cross(dir, glm::vec3(0, 1, 0)) * scale;
            break;
        case RIGHT:
            posDelta += glm::cross(dir, glm::vec3(0, 1, 0)) * scale;
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
    if (height)
        aspect = width / height;
}