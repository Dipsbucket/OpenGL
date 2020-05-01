#pragma once
#include <glad/glad.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "../ShaderLoader.h"

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
	void createToolbox(ShaderLoader shaderLoader);

	private:
	ImVec4 clear_color;
	int vs_selectedItem;
	int fs_selectedItem;
	int selectedRenderingMode, previousRenderingMode;
};
