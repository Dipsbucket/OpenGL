#include "ImGuiWindow.h"

void ImGuiWindow::clear()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

ImGuiWindow::ImGuiWindow()
{
	// Non implémenté
}

ImGuiWindow::ImGuiWindow(GLFWwindow* window, const char* glslVersion)
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
}

void ImGuiWindow::createDefault()
{
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	bool show_demo_window = true;
	bool show_another_window = true;

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);
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
			counter++;
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
			show_another_window = false;
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}