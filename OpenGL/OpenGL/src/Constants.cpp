#pragma once
#include <string>

namespace OpenGLConstants
{
	extern const unsigned int OPENGL_MAJOR_VERSION;
	extern const unsigned int OPENGL_MINOR_VERSION;
	extern const unsigned int SCREEN_WIDTH;
	extern const unsigned int SCREEN_HEIGHT;
	extern const char* GLSL_VERSION;

	extern const unsigned int IMGUI_WIDTH_OFFSET;
	extern const unsigned int IMGUI_HEIGHT_OFFSET;
}

namespace BufferConstants
{
	extern const unsigned int XYZ_PARAM_COUNT;
}

namespace ShaderConstants
{
	extern const std::string uColor;

	extern const std::string uModel;
	extern const std::string uView;
	extern const std::string uProjection;
}

namespace TransformConstants
{
	extern const double ROTATION_SENSITIVITY;
	extern const double MAX_PITCH;
}