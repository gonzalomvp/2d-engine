#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GfxUtils.h"
#include "Vec2.h"
#include "Sprite.h"

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

	// Cargamos la textura y creamos el sprite
	ltex_t* beeTexture = loadTexture("data/bee_anim.png");
	Sprite  beeSprite(beeTexture, 8, 1);
	beeSprite.setFps(8);
	beeSprite.setPivot(Vec2(0.5, 0.5));

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
		beeSprite.update(deltaTime);

		// Calculamos la direccion de movimiento y la nueva posicion
		Vec2 direction = cursor - beeSprite.getPosition();
		if (abs(direction.x) < 1) direction.x = 0;
		if (abs(direction.y) < 1) direction.y = 0;
		beeSprite.setPosition(beeSprite.getPosition() + (direction.normalize() * 128 * deltaTime));

		// Calculamos el angulo de giro
		float angle = beeSprite.getAngle();
		float targetAngle = angle;
		if (direction.x > 0)  targetAngle = -15.0f;
		if (direction.x < 0)  targetAngle =  15.0f;
		if (direction.x == 0 && direction.y == 0) targetAngle = 0.0f;

		if (targetAngle > angle) {
			angle += 5 * deltaTime;
			if (angle > targetAngle) angle = targetAngle;
		}
		if (targetAngle < angle) {
			angle -= 5 * deltaTime;
			if (angle < targetAngle) angle = targetAngle;
		}
		beeSprite.setAngle(angle);

		// Pintado
		lgfx_clearcolorbuffer(0, 0, 0);
		lgfx_setcolor(1, 1, 1, 1);

		beeSprite.draw();

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// Liberamos la textura
	ltex_free(beeTexture);

	return 0;
}
