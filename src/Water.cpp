//
// Created by edai on 10/05/18.
//

#include "Water.hpp"

Water* Water::instance = nullptr;

void Water::Init()
{
    waterTexture = SOIL_load_OGL_texture(WATER_TEXTURE, SOIL_LOAD_AUTO,
                          SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
}

void Water::RenderWater()
{
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glBindTexture(GL_TEXTURE_2D, waterTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    glBegin(GL_QUADS);
    glTexCoord2f(waterSize, waterSize); glVertex3f(-x, -Skybox::size / Skybox::factorY, -Skybox::size);
    glTexCoord2f(waterSize, 0.0f); glVertex3f(x, -Skybox::size / Skybox::factorY, -Skybox::size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, -Skybox::size / Skybox::factorY, Skybox::size);
    glTexCoord2f(0.0f, waterSize); glVertex3f(-x, -Skybox::size / Skybox::factorY, Skybox::size);
    glTexCoord2f(0.0f, waterSize); glVertex3f(-x, -Skybox::size / Skybox::factorY, Skybox::size);
    glEnd();
}

void Water::RenderSkyReflexion()
{
    glBindTexture(GL_TEXTURE_2D, Skybox::Instance()->GetTexture(Skybox::Faces::MAP_POSITIVE_Y));
    glColor4f(1.0f, 1.0f, 1.0f, skyOpacity);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-Skybox::size, -Skybox::size / Skybox::factorY, -Skybox::size);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(Skybox::size, -Skybox::size / Skybox::factorY, -Skybox::size);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(Skybox::size, -Skybox::size / Skybox::factorY, Skybox::size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-Skybox::size, -Skybox::size / Skybox::factorY, Skybox::size);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-Skybox::size, -Skybox::size / Skybox::factorY, Skybox::size);
    glEnd();
}

void Water::Render(float dt)
{
    x += waterShift * dt;

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    RenderWater();
    RenderSkyReflexion();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}