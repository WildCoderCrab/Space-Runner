#include "Bullet.h"

namespace Engine
{
	const float SPEED = 830;

	Bullet::Bullet(float x, float y)
		: Entity{x, y, "res/img/bullet.png"}, m_velocity{Vector2Zero()}
	{
		m_angle = 90;

		m_shootSound = LoadSound("res/sound/shoot.wav");
		m_hitSound = LoadSound("res/sound/hit.wav");
	}

	void Bullet::Update()
	{
		m_velocity.x = cos(m_angle * DEG2RAD) * SPEED;
		m_velocity.y = sin(m_angle * DEG2RAD) * SPEED;

		m_position.x += m_velocity.x * GetFrameTime();
		m_position.y += m_velocity.y * GetFrameTime();
	}

	void Bullet::Respawn(float x, float y, float angle)
	{
		PlaySound(m_shootSound);

		m_position.x = x;
		m_position.y = y;
		m_angle = angle;
	}

	void Bullet::Destroy()
	{
		PlaySound(m_hitSound);

		m_position.x = -100;
		m_position.y = -100;
		m_angle = 90;
	}
}