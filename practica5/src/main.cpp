#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GfxUtils.h"
#include "Vec2.h"
#include "Sprite.h"
#include "CircleCollider.h"

#include <glfw3.h>
#include <iostream>
#include <vector>

using namespace std;


int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, true);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}

	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);

	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	// Cargamos las texturas
	ltex_t* ballTexture   = loadTexture("data/ball.png");
	ltex_t* boxTexture    = loadTexture("data/box.png");
	ltex_t* circleTexture = loadTexture("data/circle.png");
	ltex_t* rectTexture   = loadTexture("data/rect.png");
	ltex_t* beeTexture    = loadTexture("data/bee.png");

	// Creamos los sprites
	Sprite ballSprite(ballTexture);
	ballSprite.setCollisionType(Sprite::CollisionType::COLLISION_CIRCLE);
	ballSprite.setPivot(Vec2(0.5, 0.5));

	Sprite beeSprite(beeTexture);
	beeSprite.setCollisionType(Sprite::CollisionType::COLLISION_PIXELS);
	beeSprite.setPivot(Vec2(0.5, 0.5));

	Sprite boxSprite(boxTexture);
	boxSprite.setCollisionType(Sprite::CollisionType::COLLISION_RECT);
	boxSprite.setPivot(Vec2(0.5, 0.5));

	Sprite cursorSprite(circleTexture);
	cursorSprite.setCollisionType(Sprite::CollisionType::COLLISION_CIRCLE);
	cursorSprite.setPivot(Vec2(0.5, 0.5));
	
	float scaleFactor = 0.25f;
	float scale       = 1.0f;

	// Bucle principal

	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);

		// Obtenemos la posicion del cursor
		double cursor_x;
		double cursor_y;
		glfwGetCursorPos(window, &cursor_x, &cursor_y);
		Vec2 cursor(static_cast<float>(cursor_x), static_cast<float>(cursor_y));

		// Actualizacion de logica del programa
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
			cursorSprite.setTexture(circleTexture);
			cursorSprite.setCollisionType(Sprite::CollisionType::COLLISION_CIRCLE);
		}
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			cursorSprite.setTexture(rectTexture);
			cursorSprite.setCollisionType(Sprite::CollisionType::COLLISION_RECT);
		}

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) {
			cursorSprite.setTexture(beeTexture);
			cursorSprite.setCollisionType(Sprite::CollisionType::COLLISION_PIXELS);
		}

		ballSprite.setPosition(Vec2(static_cast<float>(screenWidth) / 4, static_cast<float>(screenHeight) / 2));
		beeSprite.setPosition(Vec2(static_cast<float>(screenWidth) * 2 / 4, static_cast<float>(screenHeight) / 2));
		boxSprite.setPosition(Vec2(static_cast<float>(screenWidth) * 3 / 4, static_cast<float>(screenHeight) / 2));
		cursorSprite.setPosition(cursor);

		// Escalado
		scale += scaleFactor * deltaTime;
		if (scale >= 1.1f) {
			scale = 1.1f;
			scaleFactor = -scaleFactor;
		}
		else if (scale <= 0.9f) {
			scale = 0.9f;
			scaleFactor = -scaleFactor;
		}
		ballSprite.setScale(Vec2(scale, scale));
		boxSprite.setScale(Vec2(scale, scale));

		// Por defecto los sprites se pintan en blanco
		ballSprite.setColor  (1, 1, 1, 1);
		boxSprite.setColor   (1, 1, 1, 1);
		beeSprite.setColor   (1, 1, 1, 1);
		cursorSprite.setColor(1, 1, 1, 1);
		
		// Los sprites se tintan de rojo si hay colision
		if (cursorSprite.collides(ballSprite)) {
			cursorSprite.setColor(1, 0, 0, 1);
			ballSprite.setColor(1, 0, 0, 1);
		}

		if (cursorSprite.collides(boxSprite)) {
			cursorSprite.setColor(1, 0, 0, 1);
			boxSprite.setColor(1, 0, 0, 1);
		}

		if (cursorSprite.collides(beeSprite)) {
			cursorSprite.setColor(1, 0, 0, 1);
			beeSprite.setColor(1, 0, 0, 1);
		}

		// Pintado
		lgfx_clearcolorbuffer(0, 0, 0);
		lgfx_setcolor(1, 1, 1, 1);
		ballSprite.draw();
		beeSprite.draw();
		boxSprite.draw();
		cursorSprite.draw();

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Liberamos las texturas
	ltex_free(ballTexture);
	ltex_free(boxTexture);
	ltex_free(circleTexture);
	ltex_free(rectTexture);
	ltex_free(beeTexture);

	return 0;
}
