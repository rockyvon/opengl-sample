# version 330 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	int shininess;
};

struct LightDirectional{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct LightPoint{
	vec3 position;

	float c;
	float l;
	float q;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 fragment_position;
in vec3 fragment_normal;
in vec2 fragment_vertex_coor;

out vec4 FragColor;

uniform Material material;
uniform LightDirectional ld;
uniform LightPoint lp1;
uniform vec3 camera_position;

vec3 calculate_light_directional(LightDirectional light, vec3 normal, vec3 view_direcion)
{
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, fragment_vertex_coor));
	vec3 diffuse = light.diffuse * max(dot(normalize(-light.direction), normal), 0) * vec3(texture(material.diffuse, fragment_vertex_coor));
	vec3 specular = light.specular * pow(max(dot(reflect(light.direction, normal), view_direcion), 0), material.shininess) * vec3(texture(material.specular, fragment_vertex_coor));
	return ambient + diffuse + specular;
}

void main()
{
	vec3 result;
	vec3 normal_normalize = normalize(fragment_normal);
	vec3 view_direcion = normalize(camera_position - fragment_position);
	result += calculate_light_directional(ld, normal_normalize, view_direcion);
	FragColor = vec4(result, 1.0);

	//FragColor = vec4(1.0);
	//FragColor = mix(texture(texture_dif, fragment_vertex_coor), texture(texture_spe, fragment_vertex_coor), 0.5);
}



