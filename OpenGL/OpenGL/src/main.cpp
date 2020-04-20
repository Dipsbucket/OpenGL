#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <iostream>

#include "opengl/ui/ImGuiWindow.h"
#include "opengl/VertexBuffer.h"
#include "opengl/Shader.h"
#include "opengl/ShaderProgram.h"
#include "geom/ShapeFactory.h"
#include "utils/StringUtils.h"

// =========================================================================================================
// Primitives
// =========================================================================================================

int initOpenGL();
void printOpenGLInfos();
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void render(GLFWwindow* window, ImGuiWindow guiWindow);

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

GLFWwindow* window;

// =========================================================================================================
// Méthodes
// =========================================================================================================

int initOpenGL()
{
	// Initialisation de glfw
	glfwInit();

	// Création de la window
	const char* cTitle = StringUtils::parseString<const char*>("OpenGL");
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, cTitle, NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

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

	// Charge glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

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
	std::cout << "Version OpenGL : " << OPENGL_MAJOR_VERSION * 100 + OPENGL_MINOR_VERSION * 10 << std::endl;
	std::cout << "Version GLSL : " << GLSL_VERSION << std::endl;
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

void render(GLFWwindow* window, ImGuiWindow guiWindow)
{
	Shape triangle = ShapeFactory::buildTriangle();

	// Création et bind du buffer
	VertexBuffer vbo(triangle.vertices.data(), triangle.size);

	// Doit être appelé pour chaque attribute, ici attribute = vertex.positions
	// 1. index de l'attribute : 0 pour vertex.positions
	// 2. vertex.positions > nombre de float pour une coordonnée, ici xyz donc 3
	// 3. type de la donnée
	// 4. Forcer la normalisation
	// 5. vertex.positions > nb bytes séparant 2 coordonnées, ici 3 float par coordonnée
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Active le vertex attribute array, ici vertex.position donc 0
	glEnableVertexAttribArray(0);

	// SHADER
	Shader vs("res/shaders/vertex/default.vert", GL_VERTEX_SHADER);
	Shader fs("res/shaders/fragment/default.frag", GL_FRAGMENT_SHADER);

	ShaderProgram sp;
	sp.attachShader(vs.id);
	sp.attachShader(fs.id);
	sp.linkProgram();
	sp.validateProgram();

	vs.~Shader();
	fs.~Shader();

	while (!glfwWindowShouldClose(window))
	{
		// Ecoute d'évenements (glfw)
		processInput(window);

		// Rendu
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		sp.bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Creation de la windowGui
		guiWindow.createDefault();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	vbo.~VertexBuffer();
	sp.~ShaderProgram();
}

int main()
{
	// On ne continue pas si l'init a fail
	if (initOpenGL() != 0)
	{
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