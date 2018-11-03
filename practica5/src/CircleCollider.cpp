#include "CircleCollider.h"

CircleCollider::CircleCollider(const Sprite* sprite)
{
	m_sprite = sprite;
}

bool CircleCollider::collides(const Collider& other) const
{
	 return other.collides(m_sprite->getCenterPos(), m_sprite->getRadius());
}

bool CircleCollider::collides(const Vec2& circlePos, float circleRadius) const 
{
	return checkCircleCircle(m_sprite->getCenterPos(), m_sprite->getRadius(), circlePos, circleRadius);
}

bool CircleCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const 
{
	return checkCircleRect(m_sprite->getCenterPos(), m_sprite->getRadius(), rectPos, rectSize);
}

bool CircleCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	return checkCirclePixels(m_sprite->getCenterPos(), m_sprite->getRadius(), pixelsPos, pixelsSize, pixels);
}
