//
// Created by edai on 10/05/18.
//

#ifndef TERRAINSkybox_SKYBOX_HPP
#define TERRAINSkybox_SKYBOX_HPP

class Skybox
{
public:
    void Init();
    void Render(float dt);

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
