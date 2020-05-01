#pragma once
#include <string>

namespace OpenGLConstants
{
	extern const unsigned int OPENGL_MAJOR_VERSION = 4;
	extern const unsigned int OPENGL_MINOR_VERSION = 3;
	extern const unsigned int SCREEN_WIDTH = 1280;
	extern const unsigned int SCREEN_HEIGHT = 720;
	extern const char* GLSL_VERSION = "#version 430 core";

	extern const unsigned int IMGUI_WIDTH_OFFSET = 20;
	extern const unsigned int IMGUI_HEIGHT_OFFSET = 20;
}

namespace BufferConstants
{
	// vertex.positions {x, y, z} : 3 floats
	extern const unsigned int XYZ_PARAM_COUNT = 3;
}

namespace ShaderConstants
{
	extern const std::string uColor{ "u_Color" };
}