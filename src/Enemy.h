#pragma once

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

#include "Entity.h"

namespace Engine
{
	class Enemy : public Entity
	{
	private:
		Vector2 m_velocity;
		float m_animationTimer = 0;
	public:
		Enemy(float x, float y);

		void Update(Vector2 playerPos);
	};
}