#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 container_tex_coord;
in vec2 smile_tex_coord;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 color;

void main()
{
  FragColor = vec4 (color, 1) * mix (texture (texture0, container_tex_coord), texture (texture1, smile_tex_coord), 0.2);
///    FragColor = vec4 (1, 0, 0, 1);
}

