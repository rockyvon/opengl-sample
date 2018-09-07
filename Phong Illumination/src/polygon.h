
#include "opengl.h"
#include "shader.h"

class Polygon {
public:
	void init();

protected:
	GLuint vao, vbo, ibo;
	GLuint texture_dif, texture_spe;
	void initTexture(const char* path, GLuint *texture, GLint format);

};

class Cube : public Polygon {

public:
	void init(float length);
	void draw(ShaderManager * shader, mat4 model);
	void initCubeTexture(const char * dif_path, const char * spe_path);
private:
	void initCubeVertex();
	float length;

	float vertices_cube[32] = {
		-0.5f, -0.5f, 0.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,//вСоб╫г
		0.5f, -0.5f, 0.0f,  1.0f, -1.0f, 1.0f, 1.0f, 0.0f,//сроб╫г
		0.5f,  0.5f, 0.0f,  1.0f,  1.0f, 1.0f, 1.0f, 1.0f,//срио╫г
		-0.5f,  0.5f, 0.0f, -1.0f,  1.0f, 1.0f, 0.0f, 1.0f//вСио╫г
	};

	/*float vertices_cube[32] = {
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,//вСоб╫г
	0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,//сроб╫г
	0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,//срио╫г
	-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f//вСио╫г
	};*/
};

