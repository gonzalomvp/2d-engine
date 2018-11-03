#include "Sprite.h"
#include <cmath>

Sprite::Sprite(const ltex_t* tex, int hframes, int vframes)
{
	m_tex              = tex;
	m_hframes          = hframes;
	m_vframes          = vframes;
	m_blend            = BLEND_ALPHA;
	m_red              = 1;
	m_green            = 1;
	m_blue             = 1;
	m_alpha            = 1;
	m_pos              = Vec2(0, 0);
	m_angle            = 0;
	m_scale            = Vec2(1, 1);
	m_pivot            = Vec2(0, 0);
	m_fps              = 0;
	m_currentFrame     = 0.0f;
	m_size             = Vec2(0, 0);
	m_frameOffset      = Vec2(0, 0);

	updateSize();
	updateFrameOffset();
}

const ltex_t* Sprite::getTexture() const
{
	return m_tex;
}

void Sprite::setTexture(const ltex_t* tex)
{
	m_tex = tex;
	updateSize();
}

lblend_t Sprite::getBlend() const
{
	return m_blend;
}

void Sprite::setBlend(lblend_t mode)
{
	m_blend = mode;
}

float Sprite::getRed() const
{
	return m_red;
}

float Sprite::getGreen() const
{
	return m_green;
}

float Sprite::getBlue() const
{
	return m_blue;
}

float Sprite::getAlpha() const
{
	return m_alpha;
}

void Sprite::setColor(float r, float g, float b, float a)
{
	m_red   = r;
	m_green = g;
	m_blue  = b;
	m_alpha = a;
}

const Vec2& Sprite::getPosition() const
{
	return m_pos;
}

void Sprite::setPosition(const Vec2& pos)
{
	m_pos = pos;
}

float Sprite::getAngle() const
{
	return m_angle;
}

void Sprite::setAngle(float angle)
{
	m_angle = angle;
}

const Vec2& Sprite::getScale() const
{
	return m_scale;
}

void Sprite::setScale(const Vec2& scale)
{
	m_scale = scale;
	updateSize();
}

Vec2 Sprite::getSize() const
{
	return m_size;
}

void Sprite::updateSize()
{
	if (m_tex) {
		m_size.x = m_tex->width  * m_scale.x / m_hframes;
		m_size.y = m_tex->height * m_scale.y / m_vframes;
	}
}

void Sprite::updateFrameOffset()
{
	m_frameOffset.x = 1.0f / m_hframes;
	m_frameOffset.y = 1.0f / m_vframes;
}

const Vec2& Sprite::getPivot() const
{
	return m_pivot;
}

void Sprite::setPivot(const Vec2& pivot)
{
	m_pivot = pivot;
}

int Sprite::getHframes() const
{
	return m_hframes;
}

int Sprite::getVframes() const
{
	return m_vframes;
}

void Sprite::setFrames(int hframes, int vframes)
{
	m_hframes = hframes;
	m_vframes = vframes;
	updateSize();
	updateFrameOffset();
}

int Sprite::getFps() const
{
	return m_fps;
}

void Sprite::setFps(int fps)
{
	m_fps = fps;
}

float Sprite::getCurrentFrame() const
{
	return m_currentFrame;
}

void Sprite::setCurrentFrame(int frame)
{
	m_currentFrame = static_cast<float>(frame);
}

void Sprite::update(float deltaTime)
{
	int totalFrames = m_hframes * m_vframes;
	m_currentFrame += m_fps * deltaTime;
	
	while (m_currentFrame >= totalFrames) {
		m_currentFrame -= totalFrames;
	}

	while (m_currentFrame < 0) {
		m_currentFrame += totalFrames;
	}
}

void Sprite::draw() const
{
	if (m_tex) {
		int frameToDraw = static_cast<int>(trunc(m_currentFrame));
		int row    = frameToDraw / m_hframes;
		int column = frameToDraw % m_hframes;

		Vec2 framePos(column * m_frameOffset.x, row * m_frameOffset.y);

		lgfx_setcolor(m_red, m_green, m_blue, m_alpha);
		lgfx_setblend(m_blend);
		ltex_drawrotsized(m_tex, m_pos.x, m_pos.y, m_angle, m_pivot.x, m_pivot.y, m_size.x, m_size.y, framePos.x, framePos.y, framePos.x + m_frameOffset.x, framePos.y + m_frameOffset.y);
	}
}