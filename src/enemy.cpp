#include "Enemy.h"

namespace Engine
{
	const float SPEED = 100;

	Enemy::Enemy(float x, float y)
		: Entity{x, y, "res/img/enemy.png"}, m_velocity(Vector2Zero())
	{
		SetScale(1.5, 1.5);
		SetAnimationFrames(2);
	}

	void Enemy::Update(Vector2 playerPos)
	{
		m_animationTimer += GetFrameTime();

		if (m_animationTimer >= 0.3)
        {
            AddAnimationFrames();
            m_animationTimer = 0;
        }

		if (playerPos.x < m_position.x)
			m_src.width = -20;
		else
			m_src.width = 20;

		if (Vector2Distance(m_position, playerPos) > 30)
			m_position = Vector2MoveTowards(m_position, playerPos, SPEED * GetFrameTime());
	}
}