#version 330 core
out vec4 FragColor;

in vec2 v_TexCoord;
in vec2 v_ScreenPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    FragColor = texture(u_Texture, v_TexCoord) * u_Color;
}