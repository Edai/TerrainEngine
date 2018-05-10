//
// Created by edai on 10/05/18.
//

#ifndef WaterENGINE_WATER_HPP
#define WaterENGINE_WATER_HPP

class Water
{
public:
    void Init();
    void Render(float dt);

private:
    Water() = default;
    ~Water() = default;


#pragma SINGLETON
private:
    static Water* instance;

public:
    static Water* Instance()
    {
        if (instance == nullptr)
        {
            instance = new Water();
        }
        return instance;
    }

#pragma END SINGLETON
};

#endif //WaterENGINE_WATER_HPP
