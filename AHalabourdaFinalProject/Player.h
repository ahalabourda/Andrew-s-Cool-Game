#pragma once
#include <raylib.h>
class Player
{

public:

	Player() = delete;
	Player(float startX, float startY);

	void Move(float movementX, float movementY);
	
	const float GetSize() const { return size; };
	const Color GetColour() const { return colour; }
	Vector2 GetPosition() const { return position; }
	float GetX() const { return position.x; };
	float GetY() const { return position.y; };

	void Draw() const;

private:

	const float size = 25.0f;
	const Color colour { 0, 0, 0, 255 };

	float speed = 3.0f;

	Vector2 position;
	
};