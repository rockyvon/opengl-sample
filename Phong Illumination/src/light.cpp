#include "stdafx.h"
#include "light.h"


void Light::init(ShaderManager * shader)
{
	this->shader = shader;
}

void Light::setAllLight(bool dl_enabled, bool pl_enabled, bool ps_enabled)
{
	setDirectional(dl_enabled);
	setPoint(pl_enabled);
	setSpot(ps_enabled);
}

void Light::setDirectional(bool enabled) 
{
	//设置平行光
	shader->setUniform3fv("ld.direction", 1, value_ptr(ld.direction));
	shader->setUniform3fv("ld.ambient", 1, value_ptr(enabled ? ld.ambient : BLACK_VEC3));
	shader->setUniform3fv("ld.diffuse", 1, value_ptr(enabled ? ld.diffuse : BLACK_VEC3));
	shader->setUniform3fv("ld.specular", 1, value_ptr(enabled ? ld.specular : BLACK_VEC3));
}

void Light::setPoint(bool enabled)
{
	//设置点光源
	for (int i = 0; i < LIGHT_POINT_COUNT; i++)
	{
		shader->setUniform3fv("lps[" + to_string(i) + "].position", 1, value_ptr(lps[i].position));
		shader->setUniform3fv("lps[" + to_string(i) + "].ambient", 1, value_ptr(enabled ? lps[i].ambient : BLACK_VEC3));
		shader->setUniform3fv("lps[" + to_string(i) + "].diffuse", 1, value_ptr(enabled ? lps[i].diffuse : BLACK_VEC3));
		shader->setUniform3fv("lps[" + to_string(i) + "].specular", 1, value_ptr(enabled ? lps[i].specular : BLACK_VEC3));
		shader->setUniform1f("lps[" + to_string(i) + "].c", lps[i].constant);
		shader->setUniform1f("lps[" + to_string(i) + "].l", lps[i].linear);
		shader->setUniform1f("lps[" + to_string(i) + "].q", lps[i].quadratic);
	}
}

void Light::setSpot(bool enabled)
{
	//设置聚光灯
	for (int i = 0; i < LIGHT_SPOT_COUNT; i++)
	{
		shader->setUniform3fv("lss[" + to_string(i) + "].pl.position", 1, value_ptr(lss[i].pl.position));
		//cout << "spot position x:" << lss[i].pl.position.x << ";y:" << lss[i].pl.position.y << ";z:" << lss[i].pl.position.z << endl;
		shader->setUniform3fv("lss[" + to_string(i) + "].pl.ambient", 1, value_ptr(lss[i].pl.ambient));
		shader->setUniform3fv("lss[" + to_string(i) + "].pl.diffuse", 1, value_ptr(lss[i].pl.diffuse));
		shader->setUniform3fv("lss[" + to_string(i) + "].pl.specular", 1, value_ptr(lss[i].pl.specular));
		shader->setUniform1f("lss[" + to_string(i) + "].pl.c", lss[i].pl.constant);
		shader->setUniform1f("lss[" + to_string(i) + "].pl.l", lss[i].pl.linear);
		shader->setUniform1f("lss[" + to_string(i) + "].pl.q", lss[i].pl.quadratic);
		shader->setUniform3fv("lss[" + to_string(i) + "].direction", 1, value_ptr(lss[i].direction));
		shader->setUniform1f("lss[" + to_string(i) + "].cutoff", enabled ? lss[i].cutoff : 0.0f);
	}
}
