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

	// Initialisation
	this->initConfig();
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
	this->initConfig();

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
		ImGui::Begin("Another Window", &show_another_window);
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
		{
			show_another_window = false;
		}
		ImGui::End();
	}

	this->render();
}

void ImGuiWindow::createToolbox(EventManager* eventManager)
{
	// Positionnement et dimensions
	ImGui::SetNextWindowPos(ImVec2((float)this->x, (float)this->y), ImGuiCond_Always);
	ImGui::SetNextWindowSize(ImVec2((float)this->width, (float)this->height), ImGuiCond_Always);

	// render your GUI
	ImGui::Begin("Toolbox");

	ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
	if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Rendering"))
		{
			this->createOpenGLMenu(eventManager);
			this->createShaderMenu(eventManager);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Scene"))
		{
			this->createSceneMenu(eventManager);
			this->createTransformMenu(eventManager);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera"))
		{
			this->createCameraMenu(eventManager);
			ImGui::EndTabItem();
		}

		ImGui::EndTabBar();
	}
	ImGui::Separator();

	ImGui::End();

	// Render dear imgui into screen
	this->render();
}

void ImGuiWindow::initConfig()
{
	this->ratio = (double)1 / (double)3;

	this->selectedVs = 0;
	this->selectedFs = 0;

	this->depthTest = true;
	this->selectedRenderingMode = 0;

	this->selectedCamera = 0;
	this->selectedObject = 0;

	this->translation = glm::vec3(0.0f);
}

void ImGuiWindow::createSceneMenu(EventManager* eventManager)
{
	if (ImGui::CollapsingHeader("Scene Graph"))
	{
		ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;

		if (ImGui::TreeNode("Scene"))
		{
			this->createSceneGraphTree(baseFlags, eventManager->sceneManager->scene->children);
			ImGui::TreePop();
		}
	}
}

void ImGuiWindow::createTransformMenu(EventManager* eventManager)
{
	if (eventManager->shaderManager->hasMVP())
	{
		if (ImGui::CollapsingHeader("Transform"))
		{
			std::vector<const char*> object = eventManager->sceneManager->getNames();
			ImGui::Combo("Object", &this->selectedObject, object.data(), object.size());

			glm::vec3 position = eventManager->sceneManager->getObject(this->selectedObject)->computePosition();
			ImGui::InputFloat3("Position", glm::value_ptr(position));

			ImGui::SliderFloat3("", glm::value_ptr(this->translation), -5.0f, 5.0f);
			ImGui::SameLine();
			if (ImGui::Button("Translate"))
			{
				eventManager->translateObject(this->selectedObject, this->translation);
				this->translation = glm::vec3(0.0f);
			}

			if (ImGui::Button("Translation"))
			{
			}
			ImGui::SameLine();
			if (ImGui::Button("Rotation"))
			{
			}
			ImGui::SameLine();
			if (ImGui::Button("Scale"))
			{
			}
			ImGui::SameLine();
			ImGui::Text(": Undo");

			if (ImGui::Button("Translation"))
			{
			}
			ImGui::SameLine();
			if (ImGui::Button("Rotation"))
			{
			}
			ImGui::SameLine();
			if (ImGui::Button("Scale"))
			{
			}
			ImGui::SameLine();
			ImGui::Text(": Reset");
		}
	}
}

void ImGuiWindow::createOpenGLMenu(EventManager* eventManager)
{
	if (ImGui::CollapsingHeader("OpenGL"))
	{
		ImGui::Text("Select rendering mode :");

		const char* renderingModes[]{ "Full", "Wireframe", "Points" };
		ImGui::Combo("Rendering_Mode", &this->selectedRenderingMode, renderingModes, IM_ARRAYSIZE(renderingModes));
		eventManager->switchRenderingMode(this->selectedRenderingMode);

		ImGui::Checkbox("Depth Test", &this->depthTest);
		eventManager->switchDepthTest(this->depthTest);
	}
}

void ImGuiWindow::createShaderMenu(EventManager* eventManager)
{
	if (ImGui::CollapsingHeader("Shaders"))
	{
		ImGui::Text("Load & Compile Shaders :");

		std::vector<const char*> vs_shaders = eventManager->shaderManager->getNames(GL_VERTEX_SHADER);
		std::vector<const char*> fs_shaders = eventManager->shaderManager->getNames(GL_FRAGMENT_SHADER);

		ImGui::Combo("Vertex Shader", &this->selectedVs, vs_shaders.data(), vs_shaders.size());
		ImGui::Combo("Fragment Shader", &this->selectedFs, fs_shaders.data(), fs_shaders.size());

		if (ImGui::Button("Compile"))
		{
			eventManager->switchShaders(this->selectedVs, this->selectedFs);
		}
	}
}

void ImGuiWindow::createCameraMenu(EventManager* eventManager)
{
	if (eventManager->shaderManager->hasMVP())
	{
		if (ImGui::CollapsingHeader("Camera"))
		{
			std::vector<const char*> cameras = eventManager->cameraManager->getNames();
			ImGui::Combo("Cameras", &this->selectedCamera, cameras.data(), cameras.size());
			eventManager->switchCamera(this->selectedCamera);

			// Position
			ImGui::InputFloat3("Position", glm::value_ptr(eventManager->cameraManager->getCurrentCamera()->position));
		}
	}
}

void ImGuiWindow::createSceneGraphTree(ImGuiTreeNodeFlags baseFlags, std::vector<Object3D*> children)
{
	ImGuiTreeNodeFlags leafFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;;
	ImGuiTreeNodeFlags currentFlag;

	bool nodeOpen = false;
	for (std::vector<Object3D*>::iterator iterator = children.begin(); iterator != children.end(); iterator++)
	{
		currentFlag = (*iterator)->hasChildren() ? baseFlags : leafFlags;
		nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)(*iterator)->getId(), currentFlag, (*iterator)->getNameAsChar(), (*iterator)->getId());

		if (nodeOpen)
		{
			if ((*iterator)->hasChildren())
			{
				this->createSceneGraphTree(baseFlags, (*iterator)->children);
				ImGui::TreePop();
			}
		}
	}
}