#pragma once
#include <string>
#include "raylib.h"

class Sprite
{
public:
	Sprite(const char* tex_path, float x, float y);
	~Sprite();

	void move(Vector2 movementVector, float dt, float speed);
	void draw(float scale = 1);
	bool checkCollision(Sprite& Collider, float scale=3);
	Vector2 position;

	Texture2D getTexture() const { return texture; }

protected:
	Texture2D texture;
};
