#include "World.h"

void World::addSprite(Sprite& sprite)
{
	m_sprites.push_back(&sprite);
}

void World::removeSprite(Sprite& sprite)
{
	m_sprites.erase(
		std::remove_if(m_sprites.begin(), m_sprites.end(), [&sprite](const Sprite* spriteInVector) -> bool { return &sprite == spriteInVector; })
		, m_sprites.end());
}

void World::update(float deltaTime)
{
	// Calculamos el scroll automatico para cada fondo
	for (size_t i = 0; i < m_backgrounds.size(); i++) {
		if (m_backgrounds[i]) {
			m_scrollOffsets[i] = m_scrollOffsets[i] + m_scrollSpeeds[i] * deltaTime;

			// Ajustamos para evitar overflow
			while (m_scrollOffsets[i].x >= m_backgrounds[i]->width) {
				m_scrollOffsets[i].x -= m_backgrounds[i]->width;
			}
			while (m_scrollOffsets[i].y >= m_backgrounds[i]->height) {
				m_scrollOffsets[i].y -= m_backgrounds[i]->height;
			}
			while (m_scrollOffsets[i].x <= -m_backgrounds[i]->width) {
				m_scrollOffsets[i].x += m_backgrounds[i]->width;
			}
			while (m_scrollOffsets[i].y <= -m_backgrounds[i]->height) {
				m_scrollOffsets[i].y += m_backgrounds[i]->height;
			}
		}
	}

	// Actualizamos los sprites
	for (size_t i = 0; i < m_sprites.size(); i++) {
		m_sprites[i]->update(deltaTime);
	}
}

void World::draw(const Vec2& screenSize)
{
	// Limpiado de pantalla
	lgfx_clearcolorbuffer(m_clearRed, m_clearGreen, m_clearBlue);
	lgfx_setcolor(1, 1, 1, 1);
	lgfx_setblend(BLEND_ALPHA);

	// Pintamos los fondos teniendo en cuenta el scroll automatico y de la camara
	lgfx_setorigin(0, 0);
	for (int i = m_backgrounds.size() - 1; i >= 0; i--) {
		if (m_backgrounds[i]) {
			Vec2 totalScroll = m_cameraPosition * m_scrollRatios[i] - m_scrollOffsets[i];
			Vec2 uBackground(totalScroll.x / m_backgrounds[i]->width, totalScroll.y / m_backgrounds[i]->height);
			Vec2 vBackground = uBackground + Vec2(m_mapSize.x / m_backgrounds[i]->width, m_mapSize.y / m_backgrounds[i]->height);
			ltex_drawrotsized(m_backgrounds[i], 0, 0, 0, 0, 0, m_mapSize.x, m_mapSize.y, uBackground.x, uBackground.y, vBackground.x, vBackground.y);
		}
	}

	// Pintamos los sprites
	lgfx_setorigin(m_cameraPosition.x, m_cameraPosition.y);
	for (size_t i = 0; i < m_sprites.size(); i++)
	{
		m_sprites[i]->draw();
	}
}
