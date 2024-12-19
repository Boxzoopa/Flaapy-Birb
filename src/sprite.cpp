#include "sprite.h"


Sprite::Sprite(const char* tex_path, float x, float y)
{
	texture = LoadTexture(tex_path);
	position = { x, y };
}

Sprite::~Sprite()
{
	//UnloadTexture(texture);
}

void Sprite::move(Vector2 movementVector, float dt, float speed)
{
	position.x += movementVector.x * speed * dt;
	position.y += movementVector.y * speed * dt;
}


void Sprite::draw(float scale)
{
	if (scale == 1)
	{
		DrawTexture(texture, position.x, position.y, WHITE);
		
	}
	else
	{
		Rectangle sourceRec = { 0.0f, 0.0f, static_cast<float>(texture.width), static_cast<float>(texture.height) }; // Full texture
		Rectangle destRec = { position.x, position.y, texture.width * scale, texture.height * scale }; // Scaled size
		Vector2 origin = { 0.0f, 0.0f }; // Top-left corner as origin

		DrawTexturePro(texture, sourceRec, destRec, origin, 0.0f, WHITE); // No rotation

	}
}

bool Sprite::checkCollision(Sprite& obj, float scale)
{
	Rectangle self_rect = {
		position.x, position.y, texture.width* scale, texture.height* scale
	};

	Rectangle collider_rect = {
		obj.position.x, obj.position.y, obj.getTexture().width * scale, obj.getTexture().height* scale
	};

	if (CheckCollisionRecs(self_rect, collider_rect))
	{
		return true;
	}

	return false;
}
