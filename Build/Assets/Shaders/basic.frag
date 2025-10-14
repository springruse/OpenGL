#version 460 core

in vec3 v_color;
in vec2 v_texcoord;

out vec4 f_color;

uniform float u_time;
uniform sampler2D u_texture;

void main(){
	//float offset = sin(u_time + gl_FragCoord.y);
	//f_color = vec4(v_color % offset, 1.0);

	f_color = texture(u_texture, v_texcoord) * vec4(v_color, 1.0);
}

