//
// Created by edai on 20/03/18.
//

#include "Engine.hpp"

Engine *Engine::instance = nullptr;
Camera* Engine::mainCamera = new Camera();

Engine::Engine()
{
    mainCamera->SetPosition(glm::vec3(0, - Skybox::size / Skybox::factorY + 40.0f, 0));
    mainCamera->SetLookAt(glm::vec3(0.035, - Skybox::size / Skybox::factorY + 40.0f, 0.035));

    Skybox::Instance()->Init();
    Water::Instance()->Init();
    Terrain::Instance()->Init();
}

void Engine::Update(float dt)
{
    glm::mat4 mvp;

    mainCamera->Update();
    mvp = mainCamera->ProjectionMatrix * mainCamera->ViewMatrix * mainCamera->ModelMatrix;
    glLoadMatrixf(glm::value_ptr(mvp));

    Water::Instance()->Render(dt);
    Skybox::Instance()->Render(dt);
    Terrain::Instance()->Render(dt);
}
