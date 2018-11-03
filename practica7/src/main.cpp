#ifdef _MSC_VER
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "GfxUtils.h"
#include "World.h"

#include <glfw3.h>
#include <iostream>
#include <vector>

using namespace std;

struct PlayerData {
	GLFWwindow*   window;
	World*        world;
	const ltex_t* idleTexture;
	const ltex_t* runTexture;
	float         vSpeed;
};

void updatePlayer(Sprite& playerSprite, float deltaTime) {

	// Obtenemos la informacion guardada en el userData del sprite
	PlayerData* playerData = reinterpret_cast<PlayerData*>(playerSprite.getUserData());
	GLFWwindow* window = playerData->window;
	World* world = playerData->world;
	const ltex_t* idleTexture = playerData->idleTexture;
	const ltex_t* runTexture = playerData->runTexture;
	float& vSpeed = playerData->vSpeed;

	// Establecemos los valores por defecto del sprite
	playerSprite.setTexture(idleTexture);
	playerSprite.setFrames(1, 1);
	playerSprite.setFps(0);

	// Procesamos el input
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) {
		playerSprite.setTexture(runTexture);
		playerSprite.setFrames(6, 1);
		playerSprite.setFps(8);
		playerSprite.setScale(Vec2(1.0f, 1.0f));
		world->moveSprite(playerSprite, Vec2(128.0f, 0.0f) * deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT)) {
		playerSprite.setTexture(runTexture);
		playerSprite.setFrames(6, 1);
		playerSprite.setFps(8);
		playerSprite.setScale(Vec2(-1.0f, 1.0f));
		world->moveSprite(playerSprite, Vec2(-128.0f, 0.0f) * deltaTime);
	}

	// Aplicamos la gravedad
	vSpeed += 1536.0f * deltaTime;
	if (vSpeed > 256.0f) vSpeed = 256.0f;
	bool jump = world->moveSprite(playerSprite, Vec2(0.0f, vSpeed) * deltaTime);
	if (jump) vSpeed = 0.0f;

	// Saltamos si se ha pulsado la tecla y estamos tocando suelo o techo
	if (glfwGetKey(window, GLFW_KEY_SPACE) && jump) {
		vSpeed = -512.0f;
	}
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
	ltex_t* idleTexture        = loadTexture("data/idle.png");
	ltex_t* runTexture         = loadTexture("data/run.png");
	ltex_t* backgroundTexture  = loadTexture("data/background.png");

	// Inicializamos el mundo
	World world(222.0f / 255.0f, 212.0f / 255.0f, 222.0f / 255.0f, backgroundTexture);
	world.setScrollRatio(0, 0.4f);

	// Cargamos el mapa
	if (!world.loadMap("data/map.tmx", 1)) {
		cout << "Error: No se ha podido cargar el mapa" << endl;
		return -1;
	}

	// Creamos el sprite del player
	Sprite playerSprite(idleTexture);
	playerSprite.setCallback(updatePlayer);
	playerSprite.setPosition(Vec2(1 * 32, 27 * 32));
	playerSprite.setCollisionType(Sprite::COLLISION_RECT);

	PlayerData playerData{ window , &world, idleTexture, runTexture, 0.0f };
	playerSprite.setUserData(&playerData);
	playerSprite.setCallback(updatePlayer);

	// Añadimos el sprite al mundo
	world.addSprite(playerSprite);

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

		// Actualizacion de logica del programa
		world.update(deltaTime);

		// Calculamos la posicion de la camara en funcion de la posicion del player y el tamaño de la ventana
		Vec2 maxCameraPos = world.getMapSize() - screenSize;
		Vec2 cameraPos(playerSprite.getPosition() - screenSize * 0.5);
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
	ltex_free(idleTexture);
	ltex_free(runTexture);
	ltex_free(backgroundTexture);

	return 0;
}
