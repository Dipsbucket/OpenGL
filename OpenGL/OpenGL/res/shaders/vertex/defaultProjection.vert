#version 430 core

layout (location = 0) in vec3 position;
layout (location = 5) in vec3 color;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 outColor;

void main()
{
    gl_Position = u_Projection * u_View * u_Model * vec4(position.x, position.y, position.z, 1.0);
    outColor = color;
};