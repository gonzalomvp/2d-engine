#pragma once

#include <litegfx.h>
#include <stb_truetype.h>
#include "Vec2.h"
#include "Sprite.h"

ltex_t*      loadTexture(const char* filename);
inline float clamp(float value, float inf, float sup) { return (value <= inf) ? inf : (value >= sup) ? sup : value; };
inline bool  isInBounds(float value, float inf, float sup) { return (value > inf) && (value < sup); };

class Font
{
public:
	static Font* load        (const char* filename, float height);
	float        getHeight   () const;
	Vec2         getTextSize (const char* text) const;
	void         draw        (const char* text, const Vec2& pos) const;

	~Font();

private:
	ltex_t*          m_texture;
	stbtt_bakedchar* m_chardata;
	float            m_height;

	Font();
};