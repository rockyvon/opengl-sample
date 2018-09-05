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

/*
struct Vertex
{
	vec3 position;
	vec3 normal;
	vec2 texCoords;
};

struct Texture {
	int id;
	int type;
	aiString path;
};*/

struct LightDirectional 
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	LightDirectional(vec3 dir, vec3 amb, vec3 dif, vec3 spe):direction(dir), ambient(amb), diffuse(dif), specular(spe) 
	{

	}

	LightDirectional(LightDirectional * ld) {
		direction = vec3(ld->direction);
		ambient = vec3(ld->ambient);
		diffuse = vec3(ld->diffuse);
		specular = vec3(ld->specular);
	}
};

struct LightPoint 
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	LightPoint(vec3 pos, float c, float l, float q, vec3 amb, vec3 dif, vec3 spe) :
		position(pos),
		constant(c), linear(l), quadratic(q),
		ambient(amb), diffuse(dif), specular(spe)
	{

	}
};

struct LightSpot 
{
	LightPoint pl;
	vec3 direction;
	float cutoff;
};
