//
// Created by edai on 10/05/18.
//

#include <Skybox.hpp>
#include "Terrain.hpp"

Terrain* Terrain::instance = nullptr;

void Terrain::Init()
{
    height_info = SOIL_load_image(HEIGHT_MAP_FILE, &map_width, &map_height, nullptr, SOIL_LOAD_L);
    detail_texture = SOIL_load_OGL_texture(DETAIL_MAP_FILE, SOIL_LOAD_AUTO,
                          SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    terrain_texture = SOIL_load_OGL_texture(TEXTURE_MAP_FILE, SOIL_LOAD_AUTO,
                                           SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
    if (!height_info || !detail_texture || !terrain_texture)
        throw "Fail on loading Terrain related files";
}

void Terrain::RenderIsland()
{
    float size = 1.0f;
    float scale = 0.2f;
    float step = 1.0f / 255.0f;

    glBegin(GL_QUADS);
    for (int i = 0; i < map_height - 1; ++i)
    {
        for (int j = 0; j < map_width - 1; j++)
        {
            glMultiTexCoord2f(GL_TEXTURE0, j * step, i * step);
            glMultiTexCoord2f(GL_TEXTURE1, 0, 0);
            glVertex3f(i * size, height_info[(i * map_height) + j] * scale, j * size);

            glMultiTexCoord2f(GL_TEXTURE0, j * step, (i + 1) * step);
            glMultiTexCoord2f(GL_TEXTURE1, 0, 1.0);
            glVertex3f((i + 1) * size, height_info[(i + 1) * map_height + j] * scale, j * size);

            glMultiTexCoord2f(GL_TEXTURE0, (j + 1) * step, (i + 1) * step);
            glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
            glVertex3f((i + 1) * size, height_info[(i + 1) * map_height + j + 1] * scale, (j + 1) * size);

            glMultiTexCoord2f(GL_TEXTURE0, (j + 1) * step, (i) * step);
            glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0);
            glVertex3f(i * size, height_info[i * map_height + j + 1] * scale, (j + 1) * size);
        }
    }
    glEnd();
}

void Terrain::Render(float dt)
{
    double equation[] = {0, -1, 0, 0};
    glPushMatrix();
    /*glEnable(GL_CLIP_PLANE0);
    glClipPlane(GL_CLIP_PLANE0, equation);*/
    glTranslatef(0, - Skybox::size / Skybox::factorY - 20.0f, 0);
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, terrain_texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, detail_texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);

    RenderIsland();

    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE1);
    glDisable(GL_TEXTURE_2D);
    glActiveTexture(GL_TEXTURE0);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}