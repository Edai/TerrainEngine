//
// Created by edai on 20/03/18.
//

#include <Engine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;
int GraphicalCore::old_t = 0;
int GraphicalCore::speedFactor = 1;

void GraphicalCore::Init()
{
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);
    old_t = glutGet(GLUT_ELAPSED_TIME);
}

bool GraphicalCore::Run(int ac, char **av, Options *options)
{
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH) ;
    glutInitWindowPosition(WINDOWPOS_X, WINDOWPOS_Y);
    glutInitWindowSize(options->width, options->height);
    glutCreateWindow(options->window_name.c_str());
    Init();
    glutIdleFunc(GraphicalCore::Update);
    glutReshapeFunc(GraphicalCore::Reshape);
    glutSpecialFunc(GraphicalCore::SpecialKeyHandle);
    glutKeyboardFunc(GraphicalCore::KeyboardHandle);
    glutMouseFunc(GraphicalCore::MouseButton);
    glutMotionFunc(GraphicalCore::MouseMove);
    GraphicalCore::CreateMenu();
    glutMainLoop();
    return (true);
}

void GraphicalCore::Update()
{
    int t = glutGet(GLUT_ELAPSED_TIME);
    float dt = (t - old_t) / 1000.0f;

    old_t = t;
    dt = dt * speedFactor;
    Engine::Instance()->Update(dt);
    glutSwapBuffers();
    glutPostRedisplay();
}

void GraphicalCore::KeyboardHandle(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27:
            glutLeaveMainLoop();
            break;
        default:
            return;
    }
}

void GraphicalCore::SpecialKeyHandle(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            speedFactor += 1;
            break;
        case GLUT_KEY_DOWN:
            if (speedFactor > 1)
                speedFactor -= 1;
            break;
        case GLUT_KEY_LEFT:
            break;
        case GLUT_KEY_RIGHT:
            break;
        default:
            break;
    }
}

void GraphicalCore::Reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 500);
    glMatrixMode(GL_MODELVIEW);
}

void GraphicalCore::Menu(int value)
{
    glutPostRedisplay();
}

void GraphicalCore::CreateMenu()
{
    glutCreateMenu(GraphicalCore::Menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void GraphicalCore::MouseButton(int button, int state, int x, int y)
{
}

void GraphicalCore::MouseMove(int x, int y)
{

}

GraphicalCore::GraphicalCore() = default;

GraphicalCore::~GraphicalCore() = default;