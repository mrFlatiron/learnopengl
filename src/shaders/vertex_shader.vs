#version 330 core
layout (location = 0) in vec3 aPos;
//alayout (location = 1) in vec3 aColor;
layout (location = 1) in vec2 aTexCoord;

out vec2 container_tex_coord;
out vec2 smile_tex_coord;

uniform mat4 matrix;

void main ()
{
    gl_Position = matrix  * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    container_tex_coord = aTexCoord;
    smile_tex_coord = vec2 (container_tex_coord.x * 2, container_tex_coord.y * 2);

}
