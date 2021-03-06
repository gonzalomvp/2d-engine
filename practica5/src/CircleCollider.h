#pragma once

#include "Collider.h"
#include "Sprite.h"

class CircleCollider : public Collider {
public:
	CircleCollider(const Sprite* sprite);

	virtual bool collides(const Collider& other) const;
	virtual bool collides(const Vec2& circlePos, float circleRadius) const;
	virtual bool collides(const Vec2& rectPos, const Vec2& rectSize) const;
	virtual bool collides(const Vec2& pixelsPos, const Vec2& pixelsSize, const uint8_t* pixels) const;

private:
	const Sprite* m_sprite;
};
