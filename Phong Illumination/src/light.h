#include "opengl.h"
#include "shader.h"

struct LightDirectional
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	LightDirectional(vec3 dir, vec3 amb, vec3 dif, vec3 spe) :direction(dir), ambient(amb), diffuse(dif), specular(spe)
	{

	}


	LightDirectional(vec3(), vec3(), vec3(), vec3())
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

	LightPoint(LightPoint* lp)
	{
		this->position = lp->position;
		this->constant = lp->constant;
		this->linear = lp->linear;
		this->quadratic = lp->quadratic;
		this->ambient = lp->ambient;
		this->diffuse = lp->diffuse;
		this->specular = lp->specular;
	}
};

struct LightSpot
{
	LightPoint pl;
	vec3 direction;
	float cutoff;

	LightSpot(LightPoint point, vec3 dir, float cut) :pl(point), direction(dir), cutoff(radians(cut))
	{

	}
};

class Light {
public:
	static const int LIGHT_POINT_COUNT = 1;
	static const int LIGHT_SPOT_COUNT = 1;

	void init(ShaderManager * shader);
	void setAllLight(bool dl_enabled, bool pl_enabled, bool ps_enabled);
	void setDirectional(bool enabled);
	void setPoint(bool enabled);
	void setSpot(bool enabled);
private:
	vec3 BLACK_VEC3 = vec3(0.0f);

	ShaderManager * shader;

	LightDirectional ld = new LightDirectional(vec3(-1.0f, -1.0f, -1.0f),
		vec3(0.5f, 0.5f, 0.5f),
		vec3(0.8f, 0.8f, 0.8f),
		vec3(0.5f, 0.5f, 0.5f));

	LightPoint lps[LIGHT_POINT_COUNT] = {
		LightPoint(
			vec3(4.0f, 0.0f, 0.0f),
			1.0f,
			0.09f,
			0.032f,
			vec3(0.5f, 0.5f, 0.5f),
			vec3(0.8f, 0.8f, 0.8f),
			vec3(0.8f, 0.8f, 0.8f))
	};

	LightSpot lss[LIGHT_SPOT_COUNT] = {
		LightSpot(
			LightPoint(vec3(0.0f, 0.0f, 1.0f),
				1.0f,
				0.09f,
				0.032f,
				vec3(0.5f, 0.5f, 0.5f),
				vec3(0.8f, 0.8f, 0.8f),
				vec3(0.3f, 0.3f, 0.3f)),
			vec3(0.0f, 0.0f, -1.0f),
			20.0f)
	};

};