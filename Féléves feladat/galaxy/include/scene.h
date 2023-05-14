#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "object.h"

#include <obj/model.h>

// Number of stars
#define STARS_COUNT 400

typedef struct Scene
{
	Object sun;
	Object mercury;
	Object venus;
	Object earth;
	Object moon;
	Object mars;
	Object stars[STARS_COUNT];

	Material material;
	GLuint help_image;

	bool display_help;
	bool movement_enabled;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene *scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material *material);

/**
 * Update the scene.
 */
void update_scene(Scene *scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene *scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw the background.
 */
void draw_stars();

#endif /* SCENE_H */
