#Prog_1
#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec4 color;

uniform mat4 u_MVP;
out vec4 vColor;

void main()
{
    gl_Position =  u_MVP * position;
    vColor = color;
}
#Prog_End

#Prog_2
#version 330 core
layout (location = 0) in vec4 position;
layout (location = 1) in vec2 texCoor;

uniform mat4 u_MVP; 
out vec2 vtexCoor;

void main()
{
    gl_Position =  u_MVP * position;
    vtexCoor = texCoor;
}
#Prog_End

