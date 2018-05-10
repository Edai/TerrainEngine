//
// Created by edai on 10/05/18.
//

#ifndef TERRAINSkybox_SKYBOX_HPP
#define TERRAINSkybox_SKYBOX_HPP

#include "GraphicalCore.hpp"
#define FOLDER_SKYBOX "./resources/SkyBoxForCubeMap/"

class Skybox
{
public:
    void Init();
    void Render(float dt);

    GLuint textures[6];
    const char *szCubeFaces[6] = {"SkyBox0.bmp", "SkyBox1.bmp", "SkyBox2.bmp", "SkyBox3.bmp", "SkyBox4.bmp", "SkyBox5.bmp"};
    enum FACES
    {
        MAP_POSITIVE_X = 1,
        MAP_NEGATIVE_X = 3,
        MAP_POSITIVE_Y = 4,
        MAP_NEGATIVE_Y = 2,
        MAP_POSITIVE_Z = 0,
        MAP_NEGATIVE_Z = 5
    };
private:
    Skybox() = default;
    ~Skybox() = default;

#pragma SINGLETON
    private:
        static Skybox* instance;

    public:
        static Skybox* Instance()
        {
            if (instance == nullptr)
            {
                instance = new Skybox();
            }
            return instance;
        }

#pragma END SINGLETON
};

#endif //TERRAINSkybox_SKYBOX_HPP
