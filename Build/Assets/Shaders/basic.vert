#version 460 core

layout(location = 0) in vec3 a_position;
layout (location =1) in vec3 a_color;
layout (location =2) in vec2 a_texcoord;

float frequency = 3.0;
float amplitude = 0.3;
vec3 position = a_position;

out vec3 v_color;
out vec2 v_texcoord;

uniform float u_time;
uniform mat4 u_model;

void main(){
	v_color = a_color;
	v_texcoord = a_texcoord;

	//float offset = sin(u_time * frequency + position.y) * amplitude;

	// position.x += offset;
	gl_Position = u_model * vec4(a_position, 1.0);

	//gl_Position = vec4(a_position * sin(u_time), 1.0);
}