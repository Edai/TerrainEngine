//
// Created by edai on 20/03/18.
//

#ifndef ASSIGNMENT_GRAPHICALCORE_HPP
#define ASSIGNMENT_GRAPHICALCORE_HPP

#include "Application.hpp"
#include "Camera.hpp"

class GraphicalCore
{
public:
    bool Run(int ac, char **av, Options *options);

    /* OpenGL functions */
    static void MouseButton(int button, int state, int x, int y);
    static void Update();
    static void MouseMove(int x, int y);
    static void KeyboardHandle(unsigned char key, int x, int y);
    static void SpecialKeyHandle(int key, int x, int y);
    static void Reshape(int w, int h);

    static int old_t;
    static int speedFactor;

private:
    void Init();
    void CreateMenu(void);
    static void Menu(int value);

    GraphicalCore();
    ~GraphicalCore();

#pragma SINGLETON
private:
    static GraphicalCore* instance;

public:
    static GraphicalCore* Instance()
    {
        if (instance == nullptr)
        {
            instance = new GraphicalCore();
        }
        return instance;
    }
#pragma

};

#endif //ASSIGNMENT_GRAPHICALCORE_HPP
