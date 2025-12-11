#version 430

#define GRAYSCALE	(1 << 0)
#define COLORTINT	(1 << 1)
#define SCANLINE	(1 << 2)
#define INVERT		(1 << 3)
#define GRAIN		(1 << 4)
#define DISTORT		(1 << 5)

in vec2 v_texcoord;

out vec4 f_color;

// post process controls
uniform uint u_parameters = 0;
uniform float u_time = 0;
uniform float u_intensity = 1.0;
uniform vec3 u_colorTint = vec3(1, 1, 1);

uniform sampler2D u_baseMap;

void main()
{
	vec4 color = texture(u_baseMap, v_texcoord);
	vec4 postprocess = color;

	if ((u_parameters & DISTORT) != 0) {
    float strength = 0.03 * u_intensity;
    float wave = sin(v_texcoord.y * 20.0 + u_time * 3.0);
    vec2 offset = vec2(wave * strength, 0.0);
    postprocess = texture(u_baseMap, v_texcoord + offset);
	}

	postprocess.rgb = clamp(postprocess.rgb, 0.0, 1.0);
	
	if ((u_parameters & INVERT) != 0)
    postprocess.rgb = 1.0 - postprocess.rgb;

	if ((u_parameters & GRAYSCALE) != 0)
    postprocess.rgb = vec3(dot(postprocess.rgb, vec3(0.299, 0.587, 0.114)));

	if ((u_parameters & COLORTINT) != 0)
    postprocess.rgb *= u_colorTint;

	if ((u_parameters & SCANLINE) != 0) {
    float scan = sin(v_texcoord.y * 800.0);
    postprocess.rgb *= 1.0 - (scan * 0.1);
	}

	if ((u_parameters & GRAIN) != 0) {
    float noise = fract(sin(dot(v_texcoord * u_time, vec2(12.9898,78.233))) * 43758.5453);
    postprocess.rgb += (noise - 0.5) * 0.08 * u_intensity;
	}


	f_color = postprocess;
}