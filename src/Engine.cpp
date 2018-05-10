//
// Created by edai on 20/03/18.
//

#include "Engine.hpp"

Engine *Engine::instance = nullptr;

Engine::Engine()
{
    Skybox::Instance()->Init();
    Water::Instance()->Init();
    Terrain::Instance()->Init();
}

void Engine::Update(float dt)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    Skybox::Instance()->Render(dt);
    Water::Instance()->Render(dt);
    Terrain::Instance()->Render(dt);
}
