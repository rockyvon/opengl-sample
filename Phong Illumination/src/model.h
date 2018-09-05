#pragma once

#include "opengl.h"
#include "shader.h"
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace Assimp;

class Model {
public:
	void draw(ShaderManager * shader);
	void load_model(const char* path);
private:
	vector<Mesh> meshes;
	string directory;
	
	void processNode(aiNode * node, const aiScene * scene);
	Mesh processMesh(aiMesh * mesh, const aiScene * scene);
	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType aiType,
		LIGHT_MODEL type);
};