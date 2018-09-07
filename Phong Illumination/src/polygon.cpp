#include "stdafx.h"
#include "polygon.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"



void Polygon::init()
{
	
}

void Polygon::initTexture(const char* path, GLuint *texture, GLint format)
{
	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, *texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	int width, height, nrChannels;

	unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << path << std::endl;
	}
	stbi_image_free(data);
}

void Cube::init(float length = 1.0f)
{
	this->length = length;
	vertices_cube[0] = vertices_cube[1] = vertices_cube[9] = vertices_cube[24] = -length / 2;
	vertices_cube[8] = vertices_cube[16] = vertices_cube[17] = vertices_cube[25] = length / 2;
	initCubeVertex();
}

void Cube::initCubeVertex()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_cube), vertices_cube, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void *)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

void Cube::initCubeTexture(const char * dif_path, const char * spe_path)
{
	initTexture(dif_path, &texture_dif, GL_RGBA);
	initTexture(spe_path, &texture_spe, GL_RGBA);
}

void Cube::draw(ShaderManager * shader, mat4 model)
{
	glBindVertexArray(vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture_dif);
	shader->setUniform1i("material.diffuse0", 0);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture_spe);
	shader->setUniform1i("material.specular0", 1);
	shader->setUniform1i("material.shininess", 32);

	//前面
	mat4 model_local = translate(model, vec3(0.0f, 0.0f, length/2));
	shader->setUniformMatrix4fv("model", 1, value_ptr(model_local));
	glDrawArrays(GL_POLYGON, 0, 4);
	//后面
	model_local = rotate(model_local, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
	model_local = translate(model_local, vec3(0.0f, 0.0f, length));
	shader->setUniformMatrix4fv("model", 1, value_ptr(model_local));
	glDrawArrays(GL_POLYGON, 0, 4);
	//右面
	model_local = rotate(model, radians(90.0f), vec3(0.0f, 1.0f, 0.0f));
	model_local = translate(model_local, vec3(0.0f, 0.0f, length / 2));
	shader->setUniformMatrix4fv("model", 1, value_ptr(model_local));
	glDrawArrays(GL_POLYGON, 0, 4);
	//左面
	model_local = rotate(model_local, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
	model_local = translate(model_local, vec3(0.0f, 0.0f, length));
	shader->setUniformMatrix4fv("model", 1, value_ptr(model_local));
	glDrawArrays(GL_POLYGON, 0, 4);
	//下面
	model_local = rotate(model, radians(90.0f), vec3(2.0f, 0.0f, 0.0f));
	model_local = translate(model_local, vec3(0.0f, 0.0f, length / 2));
	shader->setUniformMatrix4fv("model", 1, value_ptr(model_local));
	glDrawArrays(GL_POLYGON, 0, 4);
	//上面
	model_local = rotate(model_local, radians(180.0f), vec3(0.0f, 1.0f, 0.0f));
	model_local = translate(model_local, vec3(0.0f, 0.0f, length));
	shader->setUniformMatrix4fv("model", 1, value_ptr(model_local));
	glDrawArrays(GL_POLYGON, 0, 4);
}