#include "texture.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

GLuint load_texture(const char *filename, GLint byte_order)
{
    SDL_Surface *surface;
    GLuint texture_name;

    surface = IMG_Load(filename);

    if (surface == NULL)
    {
        printf("Error loading file: %s", filename);
        exit(1);
    }

    glGenTextures(1, &texture_name);

    glBindTexture(GL_TEXTURE_2D, texture_name);
    glTexImage2D(GL_TEXTURE_2D, 0, byte_order, surface->w, surface->h, 0, byte_order, GL_UNSIGNED_BYTE, (Pixel *)(surface->pixels));

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return texture_name;
}
