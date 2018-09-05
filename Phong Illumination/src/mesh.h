#pragma once

#include "opengl.h"
#include "shader.h"

class Mesh {
public:

	Mesh(vector<Vertex> vertices, vector<GLuint> indices, vector<Texture> textures);
	void draw(ShaderManager * shader);
private:
	GLuint vao, vbo, ebo;
	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
	void setup();
};
