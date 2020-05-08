#pragma once
#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../events/EventManager.h"

class ImGuiWindow
{
	public:
	unsigned int width, height;
	unsigned int x, y;
	double ratio;
	void clear();

	ImGuiWindow();
	ImGuiWindow(GLFWwindow* window, const char* glslVersion, int width, int height);
	void refresh(int width, int height);
	void computeDimensions(int width, int height);
	void computePosition(int width);
	void newFrame();
	void render();
	void createDefault();
	void createToolbox(EventManager* eventManager);

	private:
	ImVec4 clear_color;

	int selectedVs, selectedFs;
	bool depthTest;
	int selectedRenderingMode;
	int selectedCamera;
	int selectedObject;
	glm::vec3 translation;
	glm::vec3 rotation;

	void initConfig();
	void createSceneMenu(EventManager* eventManager);
	void createTransformMenu(EventManager* eventManager);
	void createOpenGLMenu(EventManager* eventManager);
	void createShaderMenu(EventManager* eventManager);
	void createCameraMenu(EventManager* eventManager);

	void createSceneGraphTree(ImGuiTreeNodeFlags baseFlags, std::vector<Object3D*> children);
};
