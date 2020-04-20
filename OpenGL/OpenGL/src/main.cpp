#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"

#include "ui/ImGuiWindow.h"
#include "geom/Shape.h"
#include "geom/ShapeFactory.h"
#include "utils/StringUtils.h"
#include "utils/ShaderUtils.h"

// =========================================================================================================
// Primitives
// =========================================================================================================

GLFWwindow* createOpenGLWindow(std::string title);
void configureGlfw(GLFWwindow* window);
void render(GLFWwindow* window, ImGuiWindow guiWindow);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void manageShaders();

// =========================================================================================================
// Constantes
// =========================================================================================================

const unsigned int OPENGL_MAJOR_VERSION = 4;
const unsigned int OPENGL_MINOR_VERSION = 3;
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
const char* GLSL_VERSION = "#version 430 core";

// =========================================================================================================
// Variables
// =========================================================================================================

unsigned int VBO, VAO;
unsigned int shaderProgram;

// =========================================================================================================
// Méthodes
// =========================================================================================================

GLFWwindow* createOpenGLWindow(std::string title)
{
	const char* cTitle = StringUtils::parseString<const char*>(title);
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, cTitle, NULL, NULL);
	return window;
}

void configureGlfw(GLFWwindow* window)
{
	// Détermine la version d'openGL à utiliser
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OPENGL_MAJOR_VERSION);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OPENGL_MINOR_VERSION);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Setup la window
	glfwMakeContextCurrent(window);

	// Enable synchro verticale
	glfwSwapInterval(1);

	// Gestion des redimensions de la window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	// ESC : Fermeture de la window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void manageShaders()
{
	unsigned int vs = ShaderUtils::createShader("res/shaders/vertex/default.vert", GL_VERTEX_SHADER);
	unsigned int fs = ShaderUtils::createShader("res/shaders/fragment/default.frag", GL_FRAGMENT_SHADER);

	std::list <unsigned int> sList;
	sList.push_back(vs);
	sList.push_back(fs);

	ShaderUtils::createProgram(shaderProgram, sList);
}

void render(GLFWwindow* window, ImGuiWindow guiWindow)
{
	while (!glfwWindowShouldClose(window))
	{
		// Ecoute d'évenements (glfw)
		processInput(window);

		// Rendu
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		glUseProgram(shaderProgram);
		// seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// no need to unbind it every time
		// glBindVertexArray(0);

		// Creation de la windowGui
		guiWindow.createDefault();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{
	// Initialisation de glfw
	glfwInit();

	// Création de la window
	GLFWwindow* window = createOpenGLWindow("M2 TP");
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	configureGlfw(window);

	// Charge glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// /!\ Initialisation de ImGui post Glad (func pointers)
	ImGuiWindow guiWindow(window, GLSL_VERSION);

	// Loop de rendu
	render(window, guiWindow);

	// Cleanup ImGui
	guiWindow.clear();

	// Cleanup openGL
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}