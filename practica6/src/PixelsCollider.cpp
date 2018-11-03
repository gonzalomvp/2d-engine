#include "PixelsCollider.h"

PixelsCollider::PixelsCollider(const Sprite* sprite)
{
	m_sprite = sprite;
}

bool PixelsCollider::collides(const Collider& other) const
{
	 return other.collides(m_sprite->getTopLeftPos(), m_sprite->getSize(), m_sprite->getAlphaPixels());
}

bool PixelsCollider::collides(const Vec2& circlePos, float circleRadius) const
{
	return checkCirclePixels(circlePos, circleRadius, m_sprite->getTopLeftPos(), m_sprite->getSize(), m_sprite->getAlphaPixels());
}

bool PixelsCollider::collides(const Vec2& rectPos, const Vec2& rectSize) const
{
	return checkPixelsRect(m_sprite->getTopLeftPos(), m_sprite->getSize(), m_sprite->getAlphaPixels(), rectPos, rectSize);
}

bool PixelsCollider::collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const
{
	return checkPixelsPixels(m_sprite->getTopLeftPos(), m_sprite->getSize(), m_sprite->getAlphaPixels(), pixelsPos, pixelsSize, pixels);
}
