//
// Created by edai on 10/05/18.
//

#ifndef TERRAINENGINE_TERRAIN_HPP
#define TERRAINENGINE_TERRAIN_HPP

class Terrain
{
public:
    void Init();
    void Render(float dt);

private:
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
