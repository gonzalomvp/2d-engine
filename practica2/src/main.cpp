#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <iostream>
#include <math.h>
#include <glfw3.h>
#include "GfxUtils.h"
#include "Vec2.h"

using namespace std;

#define ROTATION_FACTOR     10.0f
#define ROTATION_LIMIT_SUP  10.0f
#define ROTATION_LIMIT_INF -10.0f

#define SCALE_FACTOR        0.5f
#define SCALE_LIMIT_SUP     1.2f
#define SCALE_LIMIT_INF     0.8f

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
	ltex_t* wallTexture   = loadTexture("./data/wall.jpg");
	ltex_t* grilleTexture = loadTexture("./data/grille.png");
	ltex_t* lightTexture  = loadTexture("./data/light.png");
	ltex_t* fireTexture   = loadTexture("./data/fire.png");

	// Inicializaciones
	float ang            = 0.0f;
	float scale          = 1.0f;
	float rotationFactor = ROTATION_FACTOR;
	float scaleFactor    = SCALE_FACTOR;

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

		double cursor_x;
		double cursor_y;
		glfwGetCursorPos(window, &cursor_x, &cursor_y);
		Vec2 cursor(static_cast<float>(cursor_x), static_cast<float>(cursor_y));

		// Actualizacion de logica del programa
		scale += scaleFactor * deltaTime;
		if (scale >= SCALE_LIMIT_SUP) {
			scaleFactor = -scaleFactor;
			scale = SCALE_LIMIT_SUP;
		}
		else if (scale <= SCALE_LIMIT_INF) {
			scaleFactor = -scaleFactor;
			scale = SCALE_LIMIT_INF;
		}

		ang += rotationFactor * deltaTime;
		if (ang >= ROTATION_LIMIT_SUP) {
			rotationFactor = -rotationFactor;
			ang = ROTATION_LIMIT_SUP;
		}
		else if (ang <= ROTATION_LIMIT_INF) {
			rotationFactor = -rotationFactor;
			ang = ROTATION_LIMIT_INF;
		}
		
		// Pintado
		lgfx_setcolor(1, 1, 1, 1);
		
		// Muro
		lgfx_setblend(BLEND_SOLID);
		ltex_drawrotsized(wallTexture, 0, 0, 0, 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0, 0, static_cast<float>(screenWidth)/wallTexture->width, static_cast<float>(screenHeight)/wallTexture->height);

		// Llama
		lgfx_setblend(BLEND_ADD);
		ltex_drawrotsized(fireTexture, cursor.x, cursor.y, ang, 0.5, 0.75, fireTexture->width * scale, fireTexture->height * scale, 0, 0, 1, 1);

		// Verja
		lgfx_setblend(BLEND_ALPHA);
		ltex_drawrotsized(grilleTexture, 0, 0, 0, 0, 0, static_cast<float>(screenWidth), static_cast<float>(screenHeight), 0, 0, static_cast<float>(screenWidth) / grilleTexture->width, static_cast<float>(screenHeight) / grilleTexture->height);

		// Luz
		lgfx_setblend(BLEND_MUL);
		ltex_drawrot(lightTexture, cursor.x, cursor.y, 0, 0.5, 0.5);

		// Sombra alrededor de la luz
		float halfLightTextureWidth  = lightTexture->width  / 2.0f;
		float halfLightTextureHeight = lightTexture->height / 2.0f;

		lgfx_setblend(BLEND_SOLID);
		lgfx_setcolor(0, 0, 0, 1);
		lgfx_drawrect(0, 0, cursor.x - halfLightTextureWidth, static_cast<float>(screenHeight));
		lgfx_drawrect(cursor.x - halfLightTextureWidth, 0, static_cast<float>(screenWidth) - cursor.x + halfLightTextureWidth, cursor.y - halfLightTextureHeight);
		lgfx_drawrect(cursor.x + halfLightTextureWidth, cursor.y - halfLightTextureHeight, static_cast<float>(screenWidth) - cursor.x - halfLightTextureWidth, static_cast<float>(screenHeight) - cursor.y + halfLightTextureHeight);
		lgfx_drawrect(cursor.x - halfLightTextureWidth, cursor.y + halfLightTextureHeight, static_cast<float>(lightTexture->width), static_cast<float>(screenHeight) - cursor.y - halfLightTextureHeight);

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    return 0;
}

