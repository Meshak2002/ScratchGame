#Prog_1
#version 330 core

in vec4 vColor;
out vec4 fragColor;
void main()
{
    fragColor = vColor;
}
#Prog_End

#Prog_2
#version 330 core

uniform vec4 u_color;
uniform sampler2D u_texture;

in vec2 vtexCoor;
out vec4 fragColor;
void main()
{
    fragColor =   texture(u_texture,vtexCoor);
}
#Prog_End
