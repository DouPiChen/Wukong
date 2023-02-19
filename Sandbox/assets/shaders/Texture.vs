#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;
layout(location = 4) in float a_TilingFactor;

out vec4 v_Color;
out vec2 v_TexCoord;
out float v_TexIndex;
out float v_TilingFactor;

uniform mat4 u_Projection;
uniform mat4 u_View;


void main()
{
    v_Color = a_Color;
    v_TexCoord = a_TexCoord;
    v_TexIndex = a_TexIndex;
    v_TilingFactor = a_TilingFactor;

    //gl_Position = u_Transform * vec4(a_Position, 1.0);
    //gl_Position = u_Projection * u_View * u_Transform * vec4(a_Position, 1.0);
    gl_Position = u_Projection * u_View * vec4(a_Position, 1.0);
}


