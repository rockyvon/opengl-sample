#include "stdafx.h"
#include "mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;
	setup();
}

void Mesh::setup()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER , vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_VERTEX_ARRAY, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GL_UNSIGNED_INT), &indices[0], GL_STATIC_DRAW);

	//顶点
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));

	//法线
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

	//材质
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texCoords));

	glBindVertexArray(0);

}

void Mesh::draw(ShaderManager * shader)
{
	string name;
	int diffuse_id;
	int specular_id;
	for (unsigned int i = 0; i < textures.size; i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		if (textures[i].type == DIFFUSE) {
			name = "texture_diffuse" + diffuse_id;
			diffuse_id++;
		}else if (textures[i].type == SPECULAR) {
			name = "texture_specular" + specular_id;
			specular_id++;
		}
		shader->setUniform1f(("material." + name).c_str, i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);

	}

	// 绘制网格
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
