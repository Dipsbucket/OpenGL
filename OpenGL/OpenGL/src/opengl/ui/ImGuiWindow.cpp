#include "ImGuiWindow.h"
#include "../Constants.cpp"

#include <vector>

void ImGuiWindow::clear()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

ImGuiWindow::ImGuiWindow()
{
	// Non implémenté
	this->width = 0;
	this->height = 0;
	this->x = 0;
	this->y = 0;
	this->ratio = (double)1 / (double)3;
	this->vs_selectedItem = 0;
	this->fs_selectedItem = 0;
	this->selectedRenderingMode = 0;
	this->previousRenderingMode = 0;
}

ImGuiWindow::ImGuiWindow(GLFWwindow* window, const char* glslVersion, int width, int height)
{
	// Setup Dear ImGui context
	ImGui::CreateContext();

	// Setup les listeners
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glslVersion);

	// Définit la color par défaut
	this->clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// Initialisation
	this->ratio = (double)1 / (double)3;
	this->vs_selectedItem = 0;
	this->fs_selectedItem = 0;
	this->selectedRenderingMode = 0;
	this->previousRenderingMode = 0;

	this->refresh(width, height);
}

void ImGuiWindow::refresh(int width, int height)
{
	this->computeDimensions(width, height);
	this->computePosition(width);
}

void ImGuiWindow::computeDimensions(int width, int height)
{
	// Calcul des dimensions de la window
	double cWidth = width * this->ratio;
	this->width = (int)cWidth - OpenGLConstants::IMGUI_WIDTH_OFFSET;
	this->height = height - (OpenGLConstants::IMGUI_HEIGHT_OFFSET * 2);
}

void ImGuiWindow::computePosition(int width)
{
	// Calcul de la position de la window
	this->x = width - this->width - (OpenGLConstants::IMGUI_WIDTH_OFFSET / 2);
	this->y = OpenGLConstants::IMGUI_HEIGHT_OFFSET;
}

void ImGuiWindow::newFrame()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void ImGuiWindow::render()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiWindow::createDefault()
{
	bool show_demo_window = true;
	bool show_another_window = true;

	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		// Create a window called "Hello, world!" and append into it.
		ImGui::Begin("Hello, world!");

		// Display some text (you can use a format strings too)
		ImGui::Text("This is some useful text.");
		// Edit bools storing our window open/close state
		ImGui::Checkbox("Demo Window", &show_demo_window);
		ImGui::Checkbox("Another Window", &show_another_window);

		// Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		// Edit 3 floats representing a color
		ImGui::ColorEdit3("clear color", (float*)&clear_color);

		// Buttons return true when clicked (most widgets return true when edited/activated)
		if (ImGui::Button("Button"))
		{
			counter++;
		}
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			show_another_window = false;
		}
		ImGui::End();
	}

	this->render();
}

void ImGuiWindow::createToolbox(ShaderLoader shaderLoader)
{
	// Positionnement et dimensions
	ImGui::SetNextWindowPos(ImVec2((float)this->x, (float)this->y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2((float)this->width, (float)this->height), ImGuiCond_Always);

	// render your GUI
	ImGui::Begin("Toolbox");

	if (ImGui::CollapsingHeader("Rendering Mode"))
	{
		ImGui::Text("Select rendering mode :");

		const char* renderingModes[]{ "Full", "Wireframe", "Points" };
		ImGui::Combo("Rendering_Mode", &this->selectedRenderingMode, renderingModes, IM_ARRAYSIZE(renderingModes));

		// TODO JT : Améliorer
		if (this->selectedRenderingMode != this->previousRenderingMode)
		{
			switch (this->selectedRenderingMode)
			{
				case 0:
					glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
					break;
				case 1:
					glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
					break;
				case 2:
					glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
					break;
				default:
					break;
			}

			this->previousRenderingMode = this->selectedRenderingMode;
		}
	}

	if (ImGui::CollapsingHeader("Shaders"))
	{
		ImGui::Text("Load & Compile Shaders :");

		bool compileShader = false;

		std::vector<const char*> vs_shaders = shaderLoader.getNames(GL_VERTEX_SHADER);
		std::vector<const char*> fs_shaders = shaderLoader.getNames(GL_FRAGMENT_SHADER);

		ImGui::Combo("Vertex Shader", &this->vs_selectedItem, vs_shaders.data(), vs_shaders.size());
		ImGui::Combo("Fragment Shader", &this->fs_selectedItem, fs_shaders.data(), fs_shaders.size());

		if (ImGui::Button("Compile"))
		{
			compileShader = true;

			shaderLoader.getShaderProgram()->clear();
			shaderLoader.setCurrentVsIndex(this->vs_selectedItem);
			shaderLoader.setCurrentFsIndex(this->fs_selectedItem);
			shaderLoader.compileShaders();
		}
	}

	ImGui::End();

	// Render dear imgui into screen
	this->render();
}