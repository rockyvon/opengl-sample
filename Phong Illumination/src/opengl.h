#pragma once
#include <gl/glew.h>
#include <gl/glut.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;



enum LIGHT_MODEL
{
	AMBIENT = 0,
	DIFFUSE = 1,
	SPECULAR = 2
};

