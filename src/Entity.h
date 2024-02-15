#pragma once

#include <raylib.h>

namespace Engine
{
    class Entity
    {
    protected:
        Texture2D m_texture;
        Vector2 m_position;
        float m_width;
        float m_height;
        Rectangle m_src;
        Rectangle m_dst;
        Rectangle m_collider;
        bool showCollider;

        float m_angle;
        float m_frameX;
    public:
        Entity(float x, float y, const char* file);

        // Setters
        void SetAnimationFrames(float frames);
        void AddAnimationFrames();
        void ParallaxX(float value);
        void SetAngle(float value);
        void SetScale(float valueW, float valueH);
        void SetColliderSize(float h, float w);

        // Getters
        Vector2 GetPosition() { return m_position; };
        float GetAngle() { return m_angle; };
        Rectangle GetCollider() { return m_collider; }

        void Render();
    };
}