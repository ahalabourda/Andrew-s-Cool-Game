#pragma once
#include "raylib.h"

class Enemy
{

public:
	void MoveTowards(Vector2 position);

	void Tick();
	bool GetIsActive() const { return isActive; }

private:
	const float size = 55.0f;
	const Color colour{ 200, 30, 30, 255 };
	float speed = 2.0f;
	Vector2 position = Vector2{ 0, 0 };
	bool isActive = false;

};