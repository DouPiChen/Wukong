#version 330 core
out vec4 FragColor;

in vec3 v_Color;
in vec2 v_TexCoord;

// u_Texture samplers
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;

void main()
{
    //FragColor = texture(u_Texture1, v_TexCoord);
    //FragColor = vec4(v_Color, 1.0);
    //FragColor = texture(u_Texture1, v_TexCoord) * vec4(v_Color,1.0);
    //FragColor = mix(texture(u_Texture1, v_TexCoord), texture(u_Texture2, v_TexCoord), 0.2);
    FragColor = mix(texture(u_Texture1, v_TexCoord), texture(u_Texture2, v_TexCoord), 0.2) * vec4(v_Color,1.0);
}