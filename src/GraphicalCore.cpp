//
// Created by edai on 20/03/18.
//

#include <Engine.hpp>

GraphicalCore* GraphicalCore::instance = nullptr;
int GraphicalCore::old_t = 0;
int GraphicalCore::speedFactor = 1;
int GraphicalCore::rotate = 45;
float GraphicalCore::Gy = 0.0f;
void GraphicalCore::Init()
{
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_FLAT);
    old_t = glutGet(GLUT_ELAPSED_TIME);

}

bool GraphicalCore::Run(int ac, char **av, Options *options)
{
    try
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
    catch (std::string &e)
    {
        std::cerr << "An error occurred : " << e << " !" << std::endl;
        glutLeaveMainLoop();
        return (false);
    }
    catch (...)
    {
        std::cerr << "An unknown error occurred !" << std::endl;
        glutLeaveMainLoop();
        return (false);
    }
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
        case 'z':
            rotate += 2;
            break;
        case 's':
            rotate -= 2;
            break;
        case'e':
        std::cout << Gy << std::endl;
            Gy += 0.1f;
            break;
        case 'd':
            std::cout << Gy << std::endl;
            Gy -= 0.1f;
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
//    glutCreateMenu(GraphicalCore::Menu);
//    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


void GraphicalCore::MouseButton(int button, int state, int x, int y)
{
}

void GraphicalCore::MouseMove(int x, int y)
{

}

GraphicalCore::GraphicalCore() = default;

GraphicalCore::~GraphicalCore() = default;