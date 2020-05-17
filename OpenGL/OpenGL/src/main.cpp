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

int g_mouseIn, g_mouseInViewport;
bool g_rotate;
double xMouse, yMouse;
double xMousePress, yMousePress;

// =========================================================================================================
// Méthodes
// =========================================================================================================

int initOpenGL()
{
	// Initialisation de glfw
	glfwInit();

	// TODO JT : TEST > Anti-aliasing
	//glfwWindowHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	//glfwWindowHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glfwWindowHint(GLFW_SAMPLES, 4);

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
	glfwSetCursorPosCallback(g_window, cursor_position_callback);
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
	g_rotate = false;

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
	xMouse = xPos < g_width ? xPos : g_width;
	yMouse = yPos < g_height ? yPos : g_height;
	g_mouseInViewport = xPos <= g_width && yPos <= g_height;
	//// TODO JT : TEST
	std::cout << "xPos : " << xPos << ", yPos : " << yPos << std::endl;
	//if (g_rotate)
	//{
	//	double xOffset = xMouse - xMousePress;
	//	//double yOffset = yMouse - yMousePress;
	//	double yOffset = yMousePress - yMouse;
	//	eventManager->manageRotateCamera(xOffset, yOffset);

	//	// TODO JT : TEST
	//	xMousePress = xMouse;
	//	yMousePress = yMouse;
	//}
}

void cursor_enter_callback(GLFWwindow* window, int entered)
{
	g_mouseIn = entered;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	//{
	//	if (g_mouseInViewport)
	//	{
	//		g_rotate = true;
	//		xMousePress = xMouse;
	//		yMousePress = yMouse;
	//		std::cout << "xMousePress : " << xMousePress << ", yMousePress : " << yMousePress << std::endl;
	//	}
	//}
	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	//{
	//	g_rotate = false;
	//}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		std::cout << "button pressed" << std::endl;
		if (g_mouseInViewport)
		{
			// TODO JT : TEST
			GLfloat winZ;
			glReadPixels((GLint)xMouse, (GLint)(g_height - yMouse), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);
			std::cout << "winZ : " << winZ << std::endl;

			eventManager->manageRotateCameraArcBall((float)g_width, (float)g_height, (float)xMouse, (float)yMouse, (float)winZ);
		}
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
	eventManager = new EventManager();
	eventManager->createCameraManager(g_width, g_height);
	eventManager->createShaderManager();
	eventManager->createSceneManager();

	// Création de l'objet à rendre
	Mesh linesUnit = MeshFactory::buildLinesUnit();
	Mesh linesCoordinateSystem = MeshFactory::buildLinesCoordinateSystem(2);
	Mesh triangle = MeshFactory::buildPolygon("Triangle", 3);
	Mesh quad = MeshFactory::buildPolygon("Quad", 4);
	Mesh hexagon = MeshFactory::buildPolygon("Hexagon", 6);
	Mesh sphere = MeshFactory::buildSphere(12, 12);

	//triangle.translate(glm::vec3(1.0f, 0.0f, 0.0f));
	//glm::quat rotation = glm::quat(glm::angleAxis(glm::radians(60.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	//triangle.setQuaternion(rotation);

	// Ajout des éléments de la scène

	//eventManager->sceneManager->addObject(0, &triangle);
	eventManager->sceneManager->addObject(0, &linesUnit);
	eventManager->sceneManager->addObject(0, &linesCoordinateSystem);
	eventManager->sceneManager->addObject(0, &triangle);
	//eventManager->sceneManager->addObject(0, &hexagon);

	//eventManager->sceneManager->addObject(0, &tetrahedron);

	// Création du renderer
	Renderer renderer;

	// TODO JT : TEST > Anti-aliasing
	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glEnable(GL_MULTISAMPLE);
	//glEnable(GL_LINE_SMOOTH);
	//glEnable(GL_POLYGON_SMOOTH);

	// Propriétés de rendue
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	// TODO JT : TEST
	//glPointSize(3.0);
	//glLineWidth(2.0);

	while (!glfwWindowShouldClose(window))
	{
		// New Frame ImgGui
		guiWindow.newFrame();

		// Ecoute d'évenements (glfw)
		processInput(window);

		renderer.clearZone(0, 0, g_width, g_height);
		renderer.draw(eventManager, eventManager->sceneManager->scene);

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