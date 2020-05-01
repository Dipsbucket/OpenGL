#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Constants.h"

#include "opengl/ui/ImGuiWindow.h"
#include "opengl/Renderer.h"
#include "opengl/ShaderLoader.h"
#include "opengl/Shader.h"
#include "opengl/ShaderProgram.h"

#include "geom/MeshFactory.h"

#include "utils/StringUtils.h"

// =========================================================================================================
// Primitives
// =========================================================================================================

int initOpenGL();
void printOpenGLInfos();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void computeViewport(int width, int height);
void refreshViewport(int width, int height);
void render(GLFWwindow* window);
void test();

// =========================================================================================================
// Variables
// =========================================================================================================

GLFWwindow* g_window;
int g_width, g_height;

ImGuiWindow guiWindow;
double g_widthRatio;

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
	g_width = width - (width * g_widthRatio);
	g_height = height;

	refreshViewport(g_width, g_height);
}

void refreshViewport(int width, int height)
{
	glViewport(0, 0, width, height);
}

void render(GLFWwindow* window)
{
	// Création de l'objet à rendre
	Mesh triangle = MeshFactory::buildTriangle();

	ShaderLoader shaderLoader;
	shaderLoader.loadShaders();
	shaderLoader.compileShaders();

	// Déclaration du renderer
	Renderer renderer;

	// Propriétés de rendue
	glPointSize(3.0);
	glLineWidth(2.0);

	while (!glfwWindowShouldClose(window))
	{
		// New Frame ImgGui
		guiWindow.newFrame();

		// Ecoute d'évenements (glfw)
		processInput(window);

		renderer.clearZone(0, 0, g_width, g_height);
		renderer.draw(triangle);

		// Creation de la windowGui
		guiWindow.createToolbox(shaderLoader);
		//guiWindow.createDefault();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

void test()
{
	// Viewport et Scissor
	//glViewport(0, 0, OpenGLConstants::SCREEN_WIDTH - guiWindow.width, OpenGLConstants::SCREEN_HEIGHT);
	//glScissor(0, 0, OpenGLConstants::SCREEN_WIDTH - guiWindow.width, OpenGLConstants::SCREEN_HEIGHT);
	//glEnable(GL_SCISSOR_TEST);

	// Array to vector
	//std::vector<float> vertices;
	//vertices.assign(array_vertices, array_vertices + size_vertices);
	//std::vector<unsigned int> indexes;
	//indexes.assign(array_indexes, array_indexes + size_indexes);

	// Print le contenu d'un vecteur glm
	//std::cout << "********* color *********" << std::endl;
	//std::cout << "vec4 color : " + glm::to_string(color) << std::endl;

	// Creation de la windowGui
	// Après render.draw
	//guiWindow.createDefault();

	// Post rendering loop
	//vbo.~VertexBuffer();
	//sp.~ShaderProgram();

	//vs.~Shader();
	//fs.~Shader();

	// (*iter)
	//if (!shaders.empty())
	//{
	//	for (std::vector<Shader*>::iterator iterator = shaders.begin(); iterator != shaders.end(); iterator++)
	//	{
	//		glDetachShader(this->id, (*iterator)->id);
	//		glDeleteShader((*iterator)->id);
	//	}

	//	this->unbind();
	//}
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