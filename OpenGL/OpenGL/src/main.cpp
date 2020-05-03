#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Constants.h"

#include "opengl/ui/ImGuiWindow.h"
#include "opengl/core/Renderer.h"
#include "opengl/events/EventManager.h"
#include "opengl/geom/MeshFactory.h"

#include "utils/StringUtils.h"

// =========================================================================================================
// Primitives
// =========================================================================================================

int initOpenGL();
void printOpenGLInfos();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void cursor_position_callback(GLFWwindow* window, double xPos, double yPos);
void cursor_enter_callback(GLFWwindow* window, int entered);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
void processInput(GLFWwindow* window);
void computeViewport(int width, int height);
void refreshViewport(int width, int height);
void render(GLFWwindow* window);

// =========================================================================================================
// Variables
// =========================================================================================================

GLFWwindow* g_window;
int g_width, g_height;

ImGuiWindow guiWindow;
double g_widthRatio;

EventManager* eventManager;

Mesh* scene;

int g_mouseIn;

// =========================================================================================================
// Méthodes
// =========================================================================================================

int initOpenGL()
{
	// Initialisation de glfw
	glfwInit();

	// Création de la window
	const char* cTitle = StringUtils::parseString<const char*>("OpenGL");
	g_window = glfwCreateWindow(OpenGLConstants::SCREEN_WIDTH, OpenGLConstants::SCREEN_HEIGHT, cTitle, NULL, NULL);
	if (g_window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Détermine la version d'openGL à utiliser
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGLConstants::OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGLConstants::OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Setup la window
	glfwMakeContextCurrent(g_window);

	// Enable synchro verticale
	glfwSwapInterval(1);

	// Bind de la function gérant la redimension de la window
	glfwSetFramebufferSizeCallback(g_window, framebuffer_size_callback);

	// Bind de la souris
	glfwSetCursorEnterCallback(g_window, cursor_enter_callback);
	glfwSetMouseButtonCallback(g_window, mouse_button_callback);
	glfwSetScrollCallback(g_window, scroll_callback);

	// Charge glad: load all OpenGL function pointers
	// A faire avant tout appel à une méthode OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	g_width = OpenGLConstants::SCREEN_WIDTH;
	g_height = OpenGLConstants::SCREEN_HEIGHT;
	g_widthRatio = (double)1 / (double)3;

	printOpenGLInfos();

	return 0;
}

void printOpenGLInfos()
{
	std::cout << "********* Hardware *********" << std::endl;
	std::cout << "Fabricant : " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Carte graphique: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version OpenGL : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "Version GLSL : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	std::cout << std::endl;
	std::cout << "********* Currently running *********" << std::endl;
	std::cout << "Version OpenGL : " << OpenGLConstants::OPENGL_MAJOR_VERSION * 100 + OpenGLConstants::OPENGL_MINOR_VERSION * 10 << std::endl;
	std::cout << "Version GLSL : " << OpenGLConstants::GLSL_VERSION << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	int w_width, w_height;
	glfwGetWindowSize(window, &w_width, &w_height);

	guiWindow.refresh(w_width, w_height);
	computeViewport(width, height);
}

void cursor_position_callback(GLFWwindow* window, double xPos, double yPos)
{
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	g_mouseIn = entered;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
	}
}

void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
{
	eventManager->manageScroll(yOffset);
}

void processInput(GLFWwindow* window)
{
	// ESC : Fermeture de la window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void computeViewport(int width, int height)
{
	g_width = width - (int)(width * g_widthRatio);
	g_height = height;

	refreshViewport(g_width, g_height);
}

void refreshViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void render(GLFWwindow* window)
{
	// Création de la scène
	scene = new Mesh(0, "Scene", nullptr);

	// Création de l'objet à rendre
	Mesh triangle = MeshFactory::buildTriangle(1);
	Mesh quad = MeshFactory::buildQuad(2);
	Mesh tetrahedron = MeshFactory::buildTetrahedron(3);

	triangle.addChild(&quad);
	// Ajout des éléments de la scène
	scene->addChild(&triangle);
	scene->addChild(&tetrahedron);
	//scene->addChild(&quad);

	eventManager = new EventManager();
	eventManager->createCameraManager(g_width, g_height);
	eventManager->createShaderManager();
	eventManager->scene = scene;

	// TODO JT : TEST
	// SET OBJECT MODEL MATRIX

	// Création du renderer
	Renderer renderer;

	// Propriétés de rendue
	glEnable(GL_DEPTH_TEST);
	glPointSize(3.0);
	glLineWidth(2.0);

	while (!glfwWindowShouldClose(window))
	{
		// New Frame ImgGui
		guiWindow.newFrame();

		// Ecoute d'évenements (glfw)
		processInput(window);

		renderer.clearZone(0, 0, g_width, g_height);
		renderer.draw(scene);

		// Creation de la windowGui
		guiWindow.createToolbox(eventManager);
		//guiWindow.createDefault();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	// On ne continue pas si l'init a fail
	if (initOpenGL() != 0)
	{
		return -1;
	}

	// /!\ Initialisation de ImGui post Glad (OpenGL func pointers)
	int w_width, w_height;
	glfwGetWindowSize(g_window, &w_width, &w_height);
	guiWindow = ImGuiWindow(g_window, OpenGLConstants::GLSL_VERSION, w_width, w_height);
	computeViewport(g_width, g_height);

	// Loop de rendu
	render(g_window);

	// Cleanup ImGui
	guiWindow.clear();

	// Cleanup openGL
	glfwDestroyWindow(g_window);
	glfwTerminate();

	return 0;
}