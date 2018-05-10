//
// Created by edai on 20/03/18.
//

#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "GraphicalCore.hpp"
#include "Water.hpp"
#include "Skybox.hpp"
#include "Terrain.hpp"

#include <glm/glm.hpp>
#include <list>
#include <array>
#include <vector>

class Engine
{
public:
    Engine();
    ~Engine() = default;
    void Update(float dt);

#pragma SINGLETON
private:
    static Engine* instance;

public:
    static Engine* Instance()
    {
        if (instance == nullptr)
        {
            instance = new Engine();
        }
        return instance;
    }

#pragma END SINGLETON

};

#endif //ENGINE_HPP
