#include "Player.h"

namespace Engine
{
    float playerAnimationTimer = 0;
    float bulletTimer = 0;
    float healthDelay = 0;

    Player::Player(float x, float y)
        : Entity{x, y, "res/img/player.png"}, m_health(10)
    {
        cannon = std::make_unique<Entity>(x + 10, y, "res/img/cannon.png");

        SetAnimationFrames(2);

        m_hurtSound = LoadSound("res/sound/hurt.wav");
    }

    void Player::Update(std::unique_ptr<Bullet>& bullet)
    {
        playerAnimationTimer += GetFrameTime();
        healthDelay += GetFrameTime();

        if (playerAnimationTimer >= 0.15)
        {
            AddAnimationFrames();
            playerAnimationTimer = 0;
        }

        bulletTimer += GetFrameTime();

        if (IsMouseButtonDown(0) && bulletTimer > 0.65)
        {
            cannon->SetAngle(atan2(GetMouseY() - cannon->GetPosition().y, GetMouseX() - cannon->GetPosition().x) * RAD2DEG);
            bullet->Respawn(m_position.x + 10, m_position.y, cannon->GetAngle());
            bulletTimer = 0;
        }
    }

    void Player::Damage()
    {
        if (healthDelay > 0.8)
        {
            PlaySound(m_hurtSound);
            m_health -= 1;
            healthDelay = 0;
        }
    }

    void Player::ResetHealth()
    {
        m_health = 10;
    }
}