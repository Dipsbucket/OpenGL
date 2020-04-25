#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "glm/glm.hpp"
#include <glm\gtx\string_cast.hpp>
#include "glm/gtc/matrix_transform.hpp"

#include "Constants.h"

#include "opengl/ui/ImGuiWindow.h"
#include "opengl/Renderer.h"
#include "opengl/VertexBuffer.h"
#include "opengl/IndexBuffer.h"
#include "opengl/VertexArray.h"
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
	window = glfwCreateWindow(OpenGLConstants::SCREEN_WIDTH, OpenGLConstants::SCREEN_HEIGHT, cTitle, NULL, NULL);
	if (window == NULL)
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
	std::cout << "Version OpenGL : " << OpenGLConstants::OPENGL_MAJOR_VERSION * 100 + OpenGLConstants::OPENGL_MINOR_VERSION * 10 << std::endl;
	std::cout << "Version GLSL : " << OpenGLConstants::GLSL_VERSION << std::endl;
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

	// Création d'un vertexArray
	VertexArray vao;

	// Création et bind du VertexBuffer
	VertexBuffer vbo(quad.vertices.data(), quad.verticesSize);
	VertexBufferLayout vbl;
	vbl.push<float>(BufferConstants::POSITION_PARAMETER_COUNT);

	// Bind du vbo au Vao
	vao.attachBuffer(vbo, vbl);

	// Création et bind de l'IndexBuffer
	IndexBuffer ibo(quad.indexes.data(), quad.indexesSize);

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

	// TODO JT : TEST
	//std::cout << "********* color *********" << std::endl;
	//std::cout << "vec4 color : " + glm::to_string(color) << std::endl;

	Renderer renderer;

	while (!glfwWindowShouldClose(window))
	{
		// Ecoute d'évenements (glfw)
		processInput(window);

		renderer.clear();

		// Bind du shaderProgram
		sp.bind();

		// Récupération et assignation d'un uniform
		// Attention le ShaderProgram doit exister et être bind
		glm::vec4 color(0.9f, 0.0f, 0.0f, 1.0f);
		sp.setUniform4f(ShaderConstants::uColor, color);

		renderer.draw(vao, ibo, sp);

		// Creation de la windowGui
		guiWindow.createDefault();

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// TODO JT : TEST
	//vbo.~VertexBuffer();
	//sp.~ShaderProgram();
}

int main()
{
	// On ne continue pas si l'init a fail
	if (initOpenGL() != 0)
	{
		return -1;
	}

	// /!\ Initialisation de ImGui post Glad (OpenGL func pointers)
	ImGuiWindow guiWindow(window, OpenGLConstants::GLSL_VERSION);

	// Loop de rendu
	render(window, guiWindow);

	// Cleanup ImGui
	guiWindow.clear();

	// Cleanup openGL
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}