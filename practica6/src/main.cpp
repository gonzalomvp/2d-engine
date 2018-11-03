#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GfxUtils.h"
#include "Vec2.h"
#include "World.h"
#include "Sprite.h"
#include "CircleCollider.h"

#include <glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

void updateBee(Sprite& beeSprite, float deltaTime) {
	// Calculamos la direccion de movimiento y la nueva posicion
	const Vec2& cursor = *reinterpret_cast<Vec2*>(beeSprite.getUserData());
	Vec2 direction = cursor - beeSprite.getPosition();
	if (abs(direction.x) < 1) direction.x = 0;
	if (abs(direction.y) < 1) direction.y = 0;
	beeSprite.setPosition(beeSprite.getPosition() + (direction.normalize() * 128 * deltaTime));

	// Calculamos el angulo de giro
	float angle = beeSprite.getAngle();
	float targetAngle = angle;
	if (direction.x > 0)  targetAngle = -15.0f;
	if (direction.x < 0)  targetAngle = 15.0f;
	if (direction.x == 0 && direction.y == 0) targetAngle = 0.0f;

	if (targetAngle > angle) {
		angle += 32 * deltaTime;
		if (angle > targetAngle) angle = targetAngle;
	}
	if (targetAngle < angle) {
		angle -= 32 * deltaTime;
		if (angle < targetAngle) angle = targetAngle;
	}
	beeSprite.setAngle(angle);
}

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
	ltex_t* beeTexture    = loadTexture("data/bee_anim.png");
	ltex_t* levelTexture  = loadTexture("data/level.png");
	ltex_t* trees1Texture = loadTexture("data/trees1.png");
	ltex_t* trees2Texture = loadTexture("data/trees2.png");
	ltex_t* cloudsTexture = loadTexture("data/clouds.png");

	Vec2 cursor;
	// Creamos los sprites
	Sprite  beeSprite(beeTexture, 8, 1);
	beeSprite.setFps(8);
	beeSprite.setPivot(Vec2(0.5, 0.5));
	beeSprite.setCallback(updateBee);
	beeSprite.setUserData(&cursor);

	// Inicializamos el mundo
	World world(222.0f / 255.0f, 212.0f / 255.0f, 222.0f / 255.0f, levelTexture, trees1Texture, trees2Texture, cloudsTexture);
	world.setScrollRatio(0, 1.0f);
	world.setScrollRatio(1, 0.8f);
	world.setScrollRatio(2, 0.6f);
	world.setScrollRatio(3, 0.4f);
	world.setScrollSpeed(3, Vec2(-16.0f, -8.0f));

	// Establecemos el tamaño del mapa
	world.setMapSize(Vec2(static_cast<float>(levelTexture->width), static_cast<float>(levelTexture->height)));

	// Añadimos el sprite al mundo y lo establecemos como player
	world.addSprite(beeSprite);

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
		Vec2 screenSize(static_cast<float>(screenWidth), static_cast<float>(screenHeight));

		// Obtenemos la posicion del cursor
		double cursor_x;
		double cursor_y;
		glfwGetCursorPos(window, &cursor_x, &cursor_y);

		// Calculamos la posicion relativa del cursor respecto al mundo
		cursor = Vec2(static_cast<float>(cursor_x), static_cast<float>(cursor_y)) + world.getCameraPosition();

		// Actualizacion de logica del programa
		world.update(deltaTime);

		// Calculamos la posicion de la camara en funcion de la posicion del player y el tamaño de la ventana
		Vec2 maxCameraPos = world.getMapSize() - screenSize;
		Vec2 cameraPos(beeSprite.getPosition() - screenSize * 0.5);
		// Evitamos salirnos de los limites
		cameraPos = Vec2(clamp(cameraPos.x, 0, maxCameraPos.x), clamp(cameraPos.y, 0, maxCameraPos.y));
		world.setCameraPosition(cameraPos);

		// Pintado
		world.draw(screenSize);

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Liberamos las texturas
	ltex_free(beeTexture);
	ltex_free(levelTexture);
	ltex_free(trees1Texture);
	ltex_free(trees2Texture);
	ltex_free(cloudsTexture);

	return 0;
}
