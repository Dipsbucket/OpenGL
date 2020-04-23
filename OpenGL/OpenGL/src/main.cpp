#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glm/glm.hpp"
#include <iostream>

#include "opengl/ui/ImGuiWindow.h"
#include "opengl/VertexBuffer.h"
#include "opengl/IndexBuffer.h"
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
	// Création de l'objet à rendre
	//Shape triangle = ShapeFactory::buildTriangle();
	Shape quad = ShapeFactory::buildQuad();

	// Création et bind du VertexBuffer
	VertexBuffer vbo(quad.vertices.data(), quad.verticesSize);

	// Création et bind de l'IndexBuffer
	IndexBuffer ibo(quad.indexes.data(), quad.indexesSize);

	// Doit être appelé pour chaque attribute, ici attribute = vertex.positions
	// 1. index de l'attribute : 0 pour vertex.positions
	//	1.1	Doit match avec le layout 0 du VertexShader !!!
	// 2. vertex.positions > nombre de float pour une coordonnée, ici xyz donc 3
	// 3. type de la donnée
	// 4. Forcer la normalisation
	// 5. vertex.positions > nb bytes séparant 2 coordonnées, ici 3 float par coordonnée
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	// Active le vertex attribute array, ici vertex.position donc 0
	glEnableVertexAttribArray(0);

	// Création et compilation des shaders
	Shader vs("res/shaders/vertex/default.vert", GL_VERTEX_SHADER);
	Shader fs("res/shaders/fragment/default.frag", GL_FRAGMENT_SHADER);

	// Création du Shader program et assignation des shaders
	ShaderProgram sp;
	sp.attachShader(vs.id);
	sp.attachShader(fs.id);
	sp.linkProgram();
	sp.validateProgram();

	// Destruction des shaders compilés
	vs.~Shader();
	fs.~Shader();

	// Bind du shaderProgram
	sp.bind();

	// Récupération et assignation d'un uniform
	// Attention le ShaderProgram doit exister et être bind
	int u_Index = glGetUniformLocation(sp.id, "u_Color");
	assert(u_Index != -1);
	glUniform4f(u_Index, 0.9f, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window))
	{
		// Ecoute d'évenements (glfw)
		processInput(window);

		// Rendu
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Dessine avec VertexBuffer sans IndexBuffer
		// 1. Mode de dessin
		// 2. A partir de quel vertex on veut dessiner : offset possible
		// 3. Nombre de vertex a dessiner
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Dessine avec VertexBuffer et IndexBuffer
		// 1. Mode de dessin
		// 2. Nombre d'indice à dessiner
		// 3. Type de données dans l'IndexBuffer
		// 4. Pointeur vers l'IndexBuffer. No need car bind dans le constructeur
		glDrawElements(GL_TRIANGLES, quad.indexesSize, GL_UNSIGNED_INT, nullptr);

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

	// /!\ Initialisation de ImGui post Glad (OpenGL func pointers)
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