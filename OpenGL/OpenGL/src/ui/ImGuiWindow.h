#pragma once
#include <GLFW\glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class ImGuiWindow
{
	public:
	void clear();

	ImGuiWindow();
	ImGuiWindow(GLFWwindow* window, const char* glslVersion);
	void createDefault();

	private:
	ImVec4 clear_color;
};
