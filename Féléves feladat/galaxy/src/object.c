#include "object.h"
#include "texture.h"

#include <obj/load.h>
#include <obj/draw.h>

void init_object(Object *object, const char *const model_path, const char *const texture_path, const GLint texture_byte_order)
{
    load_model(&(object->model), model_path);
    object->texture_id = load_texture(texture_path, texture_byte_order);
    object->position.x = 0;
    object->position.y = 0;
    object->position.z = 0;
    object->rotation.x = 0;
    object->rotation.y = 0;
    object->rotation.z = 0;
    object->scale.x = 1;
    object->scale.y = 1;
    object->scale.z = 1;
    object->orbit_angle = 0.0;
}

void render_object(const Object *const object)
{
    glBindTexture(GL_TEXTURE_2D, object->texture_id);
    glPushMatrix();
    glTranslatef(object->position.x, object->position.y, object->position.z);
    glMatrixMode(GL_MODELVIEW);
    glRotatef(object->rotation.x, 1, 0, 0);
    glRotatef(object->rotation.y, 0, 1, 0);
    glRotatef(object->rotation.z, 0, 0, 1);
    glScalef(object->scale.x, object->scale.y, object->scale.z);
    draw_model(&(object->model));
    glPopMatrix();
}

void render_object_material(const Object *const object)
{
    glBindTexture(GL_TEXTURE_2D, object->texture_id);
    glPushMatrix();
    glTranslatef(object->position.x, object->position.y, object->position.z);
    glMatrixMode(GL_MODELVIEW);
    glRotatef(object->rotation.x, 1, 0, 0);
    glRotatef(object->rotation.y, 0, 1, 0);
    glRotatef(object->rotation.z, 0, 0, 1);
    glScalef(object->scale.x, object->scale.y, object->scale.z);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    draw_model(&(object->model));
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}
