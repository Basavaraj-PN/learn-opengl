#shader vertex
#version 330 core

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 outColor;
out vec2 v_TextCoord;

void main()
{
   gl_Position = aPos;
   outColor = color;
   v_TextCoord = texCoord;
};

#shader fragment
#version 330 core

layout (location = 0) out vec4 color;

in vec3 outColor;
in vec2 v_TextCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
   vec4 texColor = texture(u_Texture, v_TextCoord);
   color = vec4(outColor, 1.0) / u_Color * texColor;
};