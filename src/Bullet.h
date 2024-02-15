#pragma once

#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <cmath>

#include "Entity.h"

namespace Engine
{
	class Bullet : public Entity
	{
	private:
		Vector2 m_velocity;
		Sound m_shootSound;
		Sound m_hitSound;
	public:
		Bullet(float x, float y);

		void Update();
		void Respawn(float x, float y, float angle);
		void Destroy();
	};
}