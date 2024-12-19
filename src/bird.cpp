#include "bird.h"

Bird::Bird(const char* tex_path, float x, float y)
    : Sprite(tex_path, x, y) // Call the base class constructor
{
    y_velocity = -10;
    gravity = 40;
}

Bird::~Bird() {}

void Bird::update(float dt)
{
    applyGravity(dt);

    if (IsKeyPressed(KEY_SPACE))
    {
        applyFlap(dt);
    }
}

void Bird::applyGravity(float dt)
{
    position.y += y_velocity;
    y_velocity += gravity * dt;

}

void Bird::applyFlap(float dt)
{
    y_velocity = -600 * dt;
}
