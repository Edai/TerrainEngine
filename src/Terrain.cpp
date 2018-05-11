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
    std::cout << map_width << map_height << std::endl;
}

void Terrain::Render(float dt)
{
    float size = 1.0f;
    float scale = 0.1f;
    float step = 1.0f / 255.0f;
    static float h[4];

    glPushMatrix();
    glTranslatef(-Skybox::size / 2.0f, -Skybox::size / 2.0f, -Skybox::size / 2.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, terrain_texture);
    glBegin(GL_QUADS);
    for (int i = 0; i < map_height - 1; ++i)
    {
        for (int j = 0; j < map_width - 1; ++j)
        {
            h[0] = height_info[(i * map_height) + j] * scale;
            h[1] = height_info[i * map_height + j + 1] * scale;
            h[2] = height_info[(i + 1) * map_height + j] * scale;
            h[3] = height_info[(i + 1) * map_height + j + 1] * scale;
            float x1 = i * size;
            float y1 = j * size;
            float x2 = (i + 1) * size;
            float y2 = (j + 1) * size;

            glTexCoord2f(j * step, i * step);
            glVertex3f(x1,  h[0], y1);

            glTexCoord2f(j * step, (i + 1) * step);
            glVertex3f(x2, h[2], y1);

            glTexCoord2f( (j + 1) * step, (i + 1) * step);
            glVertex3f(x2, h[3], y2);

            glTexCoord2f( (j + 1) * step, (i) * step);
            glVertex3f(x1, h[1], y2);
        }
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}