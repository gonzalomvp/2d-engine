#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#define LITE_GFX_IMPLEMENTATION
#include <litegfx.h>
#include <glfw3.h>
#include <iostream>
#include <math.h>

#include "Base.h"
#include "Vec2.h"

using namespace std;

int main() {
	// Inicializamos GLFW
	if (!glfwInit()) {
		cout << "Error: No se ha podido inicializar GLFW" << endl;
		return -1;
	}
	atexit(glfwTerminate);

	// Creamos la ventana
	glfwWindowHint(GLFW_RESIZABLE, false);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Programacion 2D", nullptr, nullptr);
	if (!window) {
		cout << "Error: No se ha podido crear la ventana" << endl;
		return -1;
	}

	// Activamos contexto de OpenGL
	glfwMakeContextCurrent(window);

	// Inicializamos LiteGFX
	lgfx_setup2d(800, 600);

	// Bucle principal
	float ang = 0;
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !glfwGetKey(window, GLFW_KEY_ESCAPE)) {
		// Actualizamos delta
		float deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// Actualizamos tamaño de ventana
		int screenWidth, screenHeight;
		glfwGetWindowSize(window, &screenWidth, &screenHeight);
		lgfx_setviewport(0, 0, screenWidth, screenHeight);

		// Actualizacion de logica del programa
		
		// Obtenemos la posicion del cursor y el centro de la ventana
		double cursor_x;
		double cursor_y;
		glfwGetCursorPos(window, &cursor_x, &cursor_y);
		Vec2 cursor(static_cast<float>(cursor_x), static_cast<float>(cursor_y));
		Vec2 screenCenter(static_cast<float>(screenWidth) / 2, static_cast<float>(screenHeight) / 2);
		Vec2 size(50, 50);
		Vec2 halfSize = size / 2;

		// Calculamos la posicion del cuadrado en el centro de la ventana
		float square1Width  = 50;
		float square1Height = 50;
		Vec2  square1Center = screenCenter;
		Vec2  square1Origin = square1Center - halfSize;
		
		// Calculamos la posicion del cuadrado en las coordenadas del raton
		float square2Width  = 50;
		float square2Height = 50;
		Vec2  square2Center = cursor;
		Vec2  square2Origin = square2Center - halfSize;

		// Calculamos el angulo del circulo que rota alrededor del raton
		ang += 32 * (PI / 180) * deltaTime;
		if (ang > (PI * 2)) {
			ang -= PI * 2;
		}

		// Calculamos la matriz de rotacion. Los senos cambian de signo para mantener la rotacion anti-horaria
		Vec2 matrixR[2];
		matrixR[0] = Vec2( cos(ang), sin(ang));  //fila 1 de la matriz de rotacion
		matrixR[1] = Vec2(-sin(ang), cos(ang));  //fila 2 de la matriz de rotacion

		float circle1Width  = 50;
		float circle1Height = 50;
		Vec2  circle1Dist(100,0);
		//Vec2  circle1Center = Vec2(matrixR[0].dot(circle1Dist), matrixR[1].dot(circle1Dist)) + square2Center;
		Vec2  circle1Center = Vec2(cos(ang), -sin(ang)) * 100 + square2Center;
		Vec2  circle1Origin = circle1Center - halfSize;

		// Calculamos la distancia desde el puntero del raton al centro de la ventana
		float dist = cursor.distance(screenCenter);

		// Calculamos el angulo entre el puntero del raton y el círculo que orbita a su alrededor
		float angle = cursor.angle(circle1Center);

		// Titulo de ventana
		std::string title = "Distancia: "
			+ stringFromNumber(dist)
			+ " -- Angulo: "
			+ stringFromNumber(angle);
		glfwSetWindowTitle(window, title.c_str());

		// Pintado
		lgfx_clearcolorbuffer(0, 0, 0.5f);

		// Pintamos el cuadrado en el centro de la ventana
		lgfx_setcolor(1, 0, 0, 1);
		//lgfx_drawrect(square1Center.x - square1Width / 2, square1Center.y - square1Height / 2, square1Width, square1Height);
		lgfx_drawrect(square1Origin.x, square1Origin.y, size.x, size.y);

		// Pintamos el cuadrado en las coordenadas del raton
		lgfx_setcolor(0, 1, 0, 1);
		//lgfx_drawrect(square2Center.x - square2Width / 2, square2Center.y - square2Height / 2, square2Width, square2Height);
		lgfx_drawrect(square2Origin.x, square2Origin.y, size.x, size.y);

		// Pintamos circulo que rota alrededor del raton
		lgfx_setcolor(1, 1, 0, 1);
		//lgfx_drawoval(circle1Center.x - circle1Width / 2, circle1Center.y - circle1Height / 2, circle1Width, circle1Height);
		lgfx_drawoval(circle1Origin.x, circle1Origin.y, size.x, size.y);

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

    return 0;
}
