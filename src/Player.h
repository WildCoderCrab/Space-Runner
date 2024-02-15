#pragma once

#include <raylib.h>
#include <iostream>
#include <memory>
#include <cmath>

#include "Entity.h"
#include "Bullet.h"

namespace Engine
{
    class Player : public Entity
    {
    private:
        float m_health;
        Sound m_hurtSound;
    public:
        std::unique_ptr<Entity> cannon;
        
        Player(float x, float y);

        void Update(std::unique_ptr<Bullet>& bullet);
        void Damage();
        void ResetHealth();

        float GetHealth() { return m_health; }
    };
}