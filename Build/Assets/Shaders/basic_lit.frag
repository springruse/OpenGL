#version 460 core
 
in vec2 v_texcoord;
in vec3 v_color;
 
out vec4 f_color;

uniform struct Material
{
	sampler2D texture;
	float shininess;
	vec2 tiling;
	vec2 offset;
} u_material;
 
uniform sampler2D u_texture;
 
void main()
{
	f_color = texture(u_texture, v_texcoord) * vec4(v_color, 1);
}


