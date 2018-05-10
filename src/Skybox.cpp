//
// Created by edai on 10/05/18.
//

#include "Skybox.hpp"

Skybox* Skybox::instance = nullptr;

void Skybox::Init()
{
    for (int i = 0; i < 6; i++)
    {
        std::string s = FOLDER_SKYBOX + std::string(szCubeFaces[i]);
        textures[i] = SOIL_load_OGL_texture(s.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA);
        std::cout << s << " " << textures[i] << std::endl;
    }
}

void Skybox::Render(float dt)
{
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);

    glRotatef(GraphicalCore::rotate, 0, 1.0f, 0);
    GLfloat size = 25.0f;
    
    // Bottom Face
    glBindTexture(GL_TEXTURE_2D, textures[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Repeat texture
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size, -size / 2.0f, -size);  // Top Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size / 2.0f, -size);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size / 2.0f,  size);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size, -size / 2.0f,  size);  // Bottom Right Of The Texture and Quad
    glEnd();

    // Top Face
    glBindTexture(GL_TEXTURE_2D, textures[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size / 2.0f, -size);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size / 2.0f,  size);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size,  size / 2.0f,  size);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size,  size / 2.0f, -size);  // Top Right Of The Texture and Quad
    glEnd();

    // Front
    glBindTexture(GL_TEXTURE_2D, textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size / 2.0f,  size);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size / 2.0f,  size);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size / 2.0f,  size);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size / 2.0f,  size);  // Top Left Of The Texture and Quad
    glEnd();

    // Back Face
    glBindTexture(GL_TEXTURE_2D, textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size / 2.0f, -size);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size / 2.0f, -size);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size / 2.0f, -size);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size / 2.0f, -size);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Left face
    glBindTexture(GL_TEXTURE_2D, textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( size, -size / 2.0f, -size);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f( size,  size / 2.0f, -size);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f( size,  size / 2.0f,  size);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f( size, -size / 2.0f,  size);  // Bottom Left Of The Texture and Quad
    glEnd();

    // Right Face
    glBindTexture(GL_TEXTURE_2D, textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // No border on sides
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // No border on sides
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-size, -size / 2.0f, -size);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-size, -size / 2.0f,  size);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-size,  size / 2.0f,  size);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-size,  size / 2.0f, -size);  // Top Left Of The Texture and Quad
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
}

//
//glTranslatef(0, 0, -1.5f);
//glScalef(size / 2.0f, size / 2.0f, size / 2.0f);
