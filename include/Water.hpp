//
// Created by edai on 10/05/18.
//

#ifndef WaterENGINE_WATER_HPP
# define WaterENGINE_WATER_HPP

# include "GraphicalCore.hpp"
# include "Skybox.hpp"
# define WATER_TEXTURE "./resources/SkyBoxForCubeMap/SkyBox5.bmp"

class Water
{
public:
    void Init();
    void Render(float dt);

private:
    Water() = default;
    ~Water() = default;
    void RenderWater();
    void RenderSkyReflexion();

    GLuint waterTexture = 0;
    GLfloat waterSize = Skybox::size / 10.0f;
    GLfloat x = Skybox::size;

    GLfloat waterShift = 2.0f;
    GLfloat skyOpacity = 0.5f;

#pragma SINGLETON
private:
    static Water* instance;
public:
    static Water* Instance()
    {
        if (instance == nullptr)
            instance = new Water();
        return instance;
    }
#pragma END SINGLETON
};

#endif //WaterENGINE_WATER_HPP
