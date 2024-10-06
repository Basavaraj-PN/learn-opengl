#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 color;
out vec3 outColor;
void main()
{
   gl_Position = aPos;
   outColor = color;
};

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;
in vec3 outColor;
uniform vec4 u_Color;
void main()
{
   color = vec4(outColor, 1.0) / u_Color;
};