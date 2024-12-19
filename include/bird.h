#pragma once
#include "sprite.h"

class Bird : public Sprite 
{
public:
    Bird(const char* tex_path, float x, float y); 
    ~Bird();
    void update(float dt);
    void applyGravity(float dt);
    void applyFlap(float dt);

    float y_velocity;
    float gravity;

private:
    
};
