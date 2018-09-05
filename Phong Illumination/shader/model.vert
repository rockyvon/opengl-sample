# version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture_coor;

out vec3 fragment_position;
out vec3 fragment_normal;
out vec2 fragment_vertex_coor;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	fragment_position = position;
	fragment_normal = mat3(transpose(inverse(model))) * vertex_normal;
	fragment_vertex_coor = vertex_texture_coor;
	gl_Position = projection * view * model * vec4(position, 1.0);
}