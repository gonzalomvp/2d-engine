#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GfxUtils.h"
#include "Vec2.h"

#include <glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

#define BANNER_TEXT "Hello, world!"

struct TBanner
{
	const Font* font;
	Vec2 pos;
	int speed;
	float color_r;
	float color_g;
	float color_b;
};

void generateBanner(std::vector<TBanner>& listOfBanners, const Font* const* tFonts, int numFonts, int screenWidth, int screenHeight);
void moveBanners(std::vector<TBanner>& listOfBanners, int screenWidth, float deltaTime);
void drawBanners(const std::vector<TBanner>& listOfBanners);

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

	// Cargamos las fuentes
	const Font* tFonts[4];
	tFonts[0] = Font::load("data/sketches font.ttf", 90);
	tFonts[1] = Font::load("data/jd_digital.ttf", 50);
	tFonts[2] = Font::load("data/Comic Strip.ttf", 75);
	tFonts[3] = Font::load("data/Colleged.ttf", 60);

	// Bucle principal
	std::vector<TBanner> listOfBanners;

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
		moveBanners(listOfBanners, screenWidth, deltaTime);
		generateBanner(listOfBanners, tFonts, 4, screenWidth, screenHeight);
		
		// Pintado
		lgfx_clearcolorbuffer(0, 0, 0);
		lgfx_setcolor(1, 1, 1, 1);
		lgfx_setblend(BLEND_ALPHA);
		drawBanners(listOfBanners);

		// Actualizamos ventana y eventos
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	return 0;
}

void generateBanner(std::vector<TBanner>& listOfBanners, const Font* const* tFonts, int numFonts, int screenWidth, int screenHeight)
{
	if (rand() % 101 < 1)
	{
		TBanner text;
		text.font    = tFonts[rand() % numFonts];
		text.pos     = Vec2(static_cast<float>(screenWidth), static_cast<float>(rand() % screenHeight));
		text.speed   = rand() % 181 + 20;
		text.color_r = rand() % 101 / 100.0f;
		text.color_g = rand() % 101 / 100.0f;
		text.color_b = rand() % 101 / 100.0f;
		listOfBanners.push_back(text);
	}
}

void moveBanners(std::vector<TBanner>& listOfBanners, int screenWidth, float deltaTime)
{
	std::vector<TBanner>::iterator itText = listOfBanners.begin();
	while (itText != listOfBanners.end())
	{
		(*itText).pos.x -= (*itText).speed*deltaTime;
		if ((*itText).pos.x + (*itText).font->getTextSize(BANNER_TEXT).x < 0) {
			itText = listOfBanners.erase(itText);
		}
		else {
			itText++;
		}
	}
}

void drawBanners(const std::vector<TBanner>& listOfBanners)
{
	for (size_t i = 0; i < listOfBanners.size(); i++)
	{
		TBanner banner = listOfBanners[i];
		lgfx_setcolor(listOfBanners[i].color_r, listOfBanners[i].color_g, listOfBanners[i].color_b, 1);
		banner.font->draw(BANNER_TEXT, Vec2(banner.pos.x, banner.pos.y));
	}
}