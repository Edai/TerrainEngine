//
// Created by edai on 10/05/18.
//

#ifndef TERRAINENGINE_TERRAIN_HPP
#define TERRAINENGINE_TERRAIN_HPP

#include <glm/vec3.hpp>
#include "GraphicalCore.hpp"

# define HEIGHT_MAP_FILE "./resources/heightmap.bmp"
# define DETAIL_MAP_FILE "./resources/detail.bmp"
# define TEXTURE_MAP_FILE "./resources/terrain-texture3.bmp"

class Terrain
{
public:
    void Init();
    void Render(float dt);

private:
    int map_height = 0;
    int map_width = 0;
    GLuint detail_texture = 0;
    GLuint terrain_texture = 0;

    unsigned char* height_info = nullptr;
    Terrain() = default;
    ~Terrain() = default;

#pragma SINGLETON
private:
    static Terrain* instance;

public:
    static Terrain* Instance()
    {
        if (instance == nullptr)
        {
            instance = new Terrain();
        }
        return instance;
    }

#pragma END SINGLETON

};

#endif //TERRAINENGINE_TERRAIN_HPP
