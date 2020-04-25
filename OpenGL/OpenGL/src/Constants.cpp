#pragma once
#include <string>

namespace OpenGLConstants
{
	extern const unsigned int OPENGL_MAJOR_VERSION;
	extern const unsigned int OPENGL_MINOR_VERSION;
	extern const unsigned int SCREEN_WIDTH;
	extern const unsigned int SCREEN_HEIGHT;
	extern const char* GLSL_VERSION;
}

namespace BufferConstants
{
	// vertex.positions {x, y, z} : 3 floats
	extern const unsigned int POSITION_PARAMETER_COUNT;
}

namespace ShaderConstants
{
	extern const std::string uColor;
}