#include "scene.h"
#include "object.h"
#include "utils.h"
#include <time.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// bolygók méretezése (a távolságok csillagászati egységekben)
#define PLANET_SIZE_SCALE 50
#define DISTANCE_SCALE 4

#define MERCURY_DIAMETER_RELATIVE_TO_SUN 0.007014518
#define VENUS_DIAMETER_RELATIVE_TO_SUN 0.008698864
#define EARTH_DIAMETER_RELATIVE_TO_SUN 0.009157683
#define MOON_DIAMETER_RELATIVE_TO_SUN 0.002497341
#define MARS_DIAMETER_RELATIVE_TO_SUN 0.004872071

#define TIME_SCALE 0.001

// keringési paraméterek (távolságok csillagászati egységekben, idő években)
#define MERCURY_ORBITAL_RADIUS 0.387098
#define VENUS_ORBITAL_RADIUS 0.7233265
#define EARTH_ORBITAL_RADIUS 1
#define MOON_ORBITAL_RADIUS 0.00256
#define MARS_ORBITAL_RADIUS 1.523805

#define MERCURY_ORBITAL_PERIOD 0.240846
#define VENUS_ORBITAL_PERIOD 0.615
#define EARTH_ORBITAL_PERIOD 1
#define MOON_ORBITAL_PERIOD 0.0748
#define MARS_ORBITAL_PERIOD 1.881

void init_scene(Scene *scene)
{
    // Naprendszer betöltése
    init_object(&(scene->sun), "assets/models/sun.obj", "assets/textures/sun.jpg", GL_RGB);

    scene->sun.position.x = 4;
    scene->sun.position.y = 4;
    scene->sun.position.z = 0;
    scene->sun.scale.x = 1;
    scene->sun.scale.y = 1;
    scene->sun.scale.z = 1;

    init_object(&(scene->mercury), "assets/models/mercury.obj", "assets/textures/mercury.png", GL_RGBA);
    scene->mercury.scale.x = MERCURY_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->mercury.scale.y = MERCURY_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->mercury.scale.z = MERCURY_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;

    init_object(&(scene->venus), "assets/models/venus.obj", "assets/textures/venus.png", GL_RGBA);
    scene->venus.scale.x = VENUS_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->venus.scale.y = VENUS_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->venus.scale.z = VENUS_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;

    init_object(&(scene->earth), "assets/models/earth.obj", "assets/textures/earth.png", GL_RGBA);
    scene->earth.scale.x = EARTH_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->earth.scale.y = EARTH_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->earth.scale.z = EARTH_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;

    init_object(&(scene->moon), "assets/models/moon.obj", "assets/textures/moon.png", GL_RGBA);
    scene->moon.scale.x = MOON_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->moon.scale.y = MOON_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->moon.scale.z = MOON_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;

    init_object(&(scene->mars), "assets/models/mars.obj", "assets/textures/mars.png", GL_RGBA);
    scene->mars.scale.x = MARS_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->mars.scale.y = MARS_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;
    scene->mars.scale.z = MARS_DIAMETER_RELATIVE_TO_SUN * PLANET_SIZE_SCALE;

    scene->help_image = load_texture("assets/textures/help.png", GL_RGB);

    // Csillagok generálása
    for (int i = 0; i < STARS_COUNT; i++)
    {
        const float distance = rand_float(200, 300);
        const float scale = rand_float(0.1, 0.5);
        const float angle = rand_float(0.0, 360.0);
        const float angle1 = rand_float(0.0, 360.0);

        scene->stars[i] = scene->sun;
        scene->stars[i].position.x = distance * cos(angle);
        scene->stars[i].position.y = distance * sin(angle);
        scene->stars[i].position.z = distance * cos(angle1);
        scene->stars[i].scale.x = scale;
        scene->stars[i].scale.y = scale;
        scene->stars[i].scale.z = scale;
    }

    // Anyagtulajdonságok beállítása
    scene->material.ambient.red = 1.0f;
    scene->material.ambient.green = 1.0f;
    scene->material.ambient.blue = 1.0f;

    scene->material.diffuse.red = 1.0f;
    scene->material.diffuse.green = 1.0f;
    scene->material.diffuse.blue = 1.0f;

    scene->material.specular.red = 1.0f;
    scene->material.specular.green = 1.0f;
    scene->material.specular.blue = 1.0f;
    scene->material.shininess = 1.0f;

    scene->display_help = false;
    scene->movement_enabled = true;
}

void set_lighting()
{
    float ambient_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float diffuse_light[] = {1.0f, 1.0f, 1.0, 1.0f};
    float specular_light[] = {1.0f, 1.0f, 1.0f, 1.0f};
    float position[] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material *material)
{
    float ambient_material_color[] = {material->ambient.red, material->ambient.green, material->ambient.blue};
    float diffuse_material_color[] = {material->diffuse.red, material->diffuse.green, material->diffuse.blue};
    float specular_material_color[] = {material->specular.red, material->specular.green, material->specular.blue};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void help(GLuint Help_menu)
{
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, Help_menu);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}

void orbit(Object *orbiter, vec3 origin, float radius, float angle)
{
    orbiter->orbit_angle += angle;

    if (orbiter->orbit_angle > 360)
    {
        orbiter->orbit_angle -= 360;
    }
    if (orbiter->orbit_angle < 0)
    {
        orbiter->orbit_angle = 360 - orbiter->orbit_angle;
    }

    orbiter->position.x = origin.x + cos(orbiter->orbit_angle) * radius;
    orbiter->position.y = origin.y + sin(orbiter->orbit_angle) * radius;
}

void update_scene(Scene *scene, double time)
{
    if (scene->movement_enabled)
    {
        scene->sun.rotation.z += 1;
        scene->mercury.rotation.z += 1;
        scene->venus.rotation.z += 1;
        scene->earth.rotation.z += 1;
        scene->moon.rotation.z += 1;
        scene->mars.rotation.z += 1;

        const float base_radius = 5;
        const float base_angle = 1;

        orbit(&(scene->mercury), scene->sun.position, base_radius * MERCURY_ORBITAL_RADIUS * DISTANCE_SCALE, base_angle / MERCURY_ORBITAL_PERIOD * TIME_SCALE);
        orbit(&(scene->venus), scene->sun.position, base_radius * VENUS_ORBITAL_RADIUS * DISTANCE_SCALE, base_angle / VENUS_ORBITAL_PERIOD * TIME_SCALE);
        orbit(&(scene->earth), scene->sun.position, base_radius * DISTANCE_SCALE, base_angle / EARTH_ORBITAL_PERIOD * TIME_SCALE);
        orbit(&(scene->moon), scene->earth.position, base_radius * MOON_ORBITAL_RADIUS * DISTANCE_SCALE * PLANET_SIZE_SCALE, base_angle / MOON_ORBITAL_PERIOD * TIME_SCALE);
        orbit(&(scene->mars), scene->sun.position, base_radius * MARS_ORBITAL_RADIUS * DISTANCE_SCALE, base_angle / MARS_ORBITAL_PERIOD * TIME_SCALE);
    }
}

void render_scene(const Scene *scene)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    set_material(&(scene->material));
    set_lighting();

    draw_stars(scene);
    render_object(&(scene->sun));
    render_object_material(&(scene->mercury));
    render_object_material(&(scene->venus));
    render_object_material(&(scene->earth));
    render_object_material(&(scene->moon));
    render_object_material(&(scene->mars));

    if (scene->display_help)
    {
        help(scene->help_image);
    }
}

void draw_stars(const Scene *scene)
{
    for (int i = 0; i < STARS_COUNT; i++)
    {
        render_object(&(scene->stars[i]));
    }
}