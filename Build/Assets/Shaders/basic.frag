#version 460 core

in vec3 v_color;
out vec4 f_color;

uniform float u_time;
//layout (location = 1) in vec4 color;
//layout (location = 2) in vec2 uv;

void main(){
	float offset = sin(u_time + gl_FragCoord.y);
	f_color = vec4(v_color % offset, 1.0);
}

