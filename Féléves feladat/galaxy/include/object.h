#ifndef OBJECT_H
#define OBJECT_H

#include "utils.h"

#include <obj/model.h>
#include <GL/gl.h>

typedef struct Object
{
    Model model;
    GLuint texture_id;
    vec3 position;
    vec3 rotation;
    vec3 scale;
    float orbit_angle;
} Object;

/**
 * Initialize an object, load the model and the texture.
 */
void init_object(Object *object, const char *const model_path, const char *const texture_path, const GLint texture_byte_order);

/**
 * Draw the object on screen.
 */
void render_object(const Object *const object);

/**
 * Draw the object on screen and set the material.
 */
void render_object_material(const Object *const object);

#endif