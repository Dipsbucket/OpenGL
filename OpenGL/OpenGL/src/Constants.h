#pragma once
#include <string>

namespace OpenGLConstants
{
	extern const unsigned int OPENGL_MAJOR_VERSION = 4;
	extern const unsigned int OPENGL_MINOR_VERSION = 3;
	extern const unsigned int SCREEN_WIDTH = 1280;
	extern const unsigned int SCREEN_HEIGHT = 720;
	extern const char* GLSL_VERSION = "#version 430 core";
}

namespace BufferConstants
{
	extern const unsigned int POSITION_PARAMETER_COUNT = 3;
}

namespace ShaderConstants
{
	extern const std::string uColor{ "u_Color" };
}