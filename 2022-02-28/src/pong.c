#include "pong.h"

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

int is_left_pad_under_ball(const Pong* pong)
{
    return (pong->left_pad.y < pong->ball.y - pong->ball.radius) 
        && (pong->left_pad.y + pong->left_pad.height > pong->ball.y);
}

int is_right_pad_under_ball(const Pong* pong)
{
    return (pong->right_pad.y < pong->ball.y - pong->ball.radius) 
        && (pong->right_pad.y + pong->right_pad.height > pong->ball.y);
}

void bounce_ball(Pong* pong)
{
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
    if (pong->ball.x - pong->ball.radius <= 50) {
        if (is_left_pad_under_ball(pong)) {
            pong->ball.x = pong->ball.radius + 50;
            pong->ball.speed_x *= -1;
        }
        else {
            pong->ball.x = pong->width / 2;
            pong->ball.y = pong->height / 2;
            pong->ball.speed_x *= -1;
            pong->ball.rotation *= -1;
        }
    }
    if (pong->ball.x + pong->ball.radius >= pong->width - 50) {
        if (is_right_pad_under_ball(pong)) {
            pong->ball.x = pong->width - pong->ball.radius - 50;
            pong->ball.speed_x *= -1;
        }
        else {
            pong->ball.x = pong->width / 2;
            pong->ball.y = pong->height / 2;
            pong->ball.speed_x *= -1;
            pong->ball.rotation *= -1;
        }
    }
}
