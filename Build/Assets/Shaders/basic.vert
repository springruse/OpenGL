#version 460 core

layout(location = 0) in vec3 a_position;
layout (location =1) in vec3 a_color;
float frequency = 3.0;
float amplitude = 0.3;
vec3 position = a_position;

out vec3 v_color;
uniform float u_time;

void main(){
	v_color = a_color;
	float offset = sin(u_time * frequency + position.y) * amplitude;
	position.x += offset;
	gl_Position = vec4(position, 1.0);

	//gl_Position = vec4(a_position * sin(u_time), 1.0);
}