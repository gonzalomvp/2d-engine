#include "RectCollider.h"

RectCollider::RectCollider(const Sprite* sprite)
{
	m_sprite = sprite;
}

bool RectCollider::collides(const Collider& other) const
{
	 return other.collides(m_sprite->getTopLeftPos(), m_sprite->getSize());
}

bool RectCollider::collides(const Vec2& circlePos, float circleRadius) const
{
	return checkCircleRect(circlePos, circleRadius, m_sprite->getTopLeftPos(), m_sprite->getSize());
}

bool RectCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const 
{
	return checkRectRect(m_sprite->getTopLeftPos(), m_sprite->getSize(), rectPos, rectSize);
}

bool RectCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	return checkPixelsRect(pixelsPos, pixelsSize, pixels, m_sprite->getTopLeftPos(), m_sprite->getSize());
}
