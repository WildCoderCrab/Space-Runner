#include "Entity.h"

namespace Engine
{
    Entity::Entity(float x, float y, const char* file)
        : showCollider(false)
    {
        m_texture = LoadTexture(file);

        m_position.x = x;
        m_position.y = y;

        m_src = {0, 0, (float)m_texture.width, (float)m_texture.height};
        m_dst = {x, y, m_src.width, m_src.height};

        m_width = m_dst.width;
        m_height = m_dst.height;

        m_angle = 0;

        m_collider = {m_dst.x, m_dst.y, m_dst.width, m_dst.height};
    }

    void Entity::SetAnimationFrames(float frame)
    {
        m_src.width /= frame;
        m_width /= frame;
    }

    void Entity::AddAnimationFrames()
    {
        m_src.x += m_src.width;
    }

    void Entity::ParallaxX(float value)
    {
        m_src.x += value * GetFrameTime();
    }

    void Entity::SetAngle(float value)
    {
        m_angle = value;
    }

    void Entity::SetScale(float valueW, float valueH)
    {
        m_width *= valueW;
        m_height *= valueH;
    }

    void Entity::SetColliderSize(float w, float h)
    {
        m_collider.width = w;
        m_collider.height = h;
    }

    void Entity::Render()
    {
        m_dst.x = m_position.x;
        m_dst.y = m_position.y;
        m_dst.width = m_width;
        m_dst.height = m_height;

        m_collider.x = m_dst.x - m_width / 2;
        m_collider.y = m_dst.y - m_height / 2;
        m_collider.width = m_width;
        m_collider.height = m_height;

        DrawTexturePro(m_texture, m_src, m_dst, {m_dst.width / 2, m_dst.height / 2}, m_angle, WHITE);

        if (showCollider)
            DrawRectangleRec(m_collider, BLUE);
    }
}