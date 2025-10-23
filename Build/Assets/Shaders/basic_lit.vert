#version 460 core
 
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec2 a_texcoord;
layout (location = 2) in vec3 a_normal;
 
out vec2 v_texcoord;
out vec3 v_color;
 
uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

uniform vec3 u_ambient_light; 


uniform struct Light
{
	vec3 position;
	vec3 color;
} u_light;

vec3 calculateLight(in vec3 position, in vec3 normal)
{
	//diffuse
	vec3 light_dir = normalize(u_light.position - position);
	float intensity = max(dot(light_dir, normal), 0);
	vec3 diffuse = u_light.color * intensity;

	//specular
	vec3 reflection = reflect(-light_dir, normal);
	vec3 view_dir = normalize(-position);
	intensity = max(dot(reflection, view_dir), 0);
	intensity = pow(intensity, 128);
	vec3 specular = vec3(intensity);

	return u_ambient_light + diffuse + specular;
}

void main()
{
	v_texcoord = a_texcoord;
	
	mat4 model_view = u_model * u_model;
	vec3 position = vec3(model_view * vec4(a_position,1));
	vec3 normal = normalize(mat3(model_view) * a_normal);

	v_color = calculateLight(position, normal);
	
	gl_Position = u_projection * u_view * u_model * vec4(a_position, 1.0);
}
