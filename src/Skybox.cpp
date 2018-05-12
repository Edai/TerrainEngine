//
// Created by edai on 10/05/18.
//

#include "Skybox.hpp"

Skybox* Skybox::instance = nullptr;
GLfloat Skybox::size = 1000.0f;
GLfloat Skybox::factorY = 3.0f;

void Skybox::Init()
{
    for (int i = 0; i < 5; i++)
    {
        std::string s = FOLDER_SKYBOX + std::string(faces_names[i]);
        textures[i] = SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO,
                                            SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
        if (!textures[i])
            throw "Texture file \"" + s + "\" cannot be found";
    }
}

void Skybox::ApplyTexture(GLuint t)
{
    glBindTexture(GL_TEXTURE_2D, t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::Render(float dt)
{
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    ApplyTexture(textures[MAP_POSITIVE_Y]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size / factorY, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size / factorY, size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(size, size / factorY, size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(size, size / factorY, -size);
    glEnd();

    ApplyTexture(textures[MAP_NEGATIVE_X]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size / factorY, size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size / factorY, size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size / factorY, size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size / factorY, size);
    glEnd();

    ApplyTexture(textures[MAP_POSITIVE_X]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size / factorY, -size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size / factorY, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size / factorY, -size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size / factorY, -size);
    glEnd();

    ApplyTexture(textures[MAP_NEGATIVE_Y]);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(size, -size / factorY, -size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(size, size / factorY, -size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(size, size / factorY, size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(size, -size / factorY, size);
    glEnd();

    ApplyTexture(textures[MAP_POSITIVE_Z]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size / factorY, -size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size / factorY, size);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, size / factorY, size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, size / factorY, -size);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

GLuint Skybox::GetTexture(int i)
{
    return textures[i];
}
