#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

#include "model.h"
#include "mesh.h"
#include "texture.h"
#include "vertex.h"
#include "shader_program.h"


class SimpleModel : public Model{
protected:
	vector <Mesh*> meshes;
	vector <Texture*> textures;
	
	virtual bool parse_scene(const aiScene *pScene, string &model_file);
	bool load_textures(const aiScene* pScene, const string &model_file);
	bool load_texture_from_material(aiMaterial *material, string &dir, Texture **texture);
public:
	SimpleModel(ShaderProgram *shaderProgram, Model *model);
	virtual ~SimpleModel();
	virtual void clear();
	bool load(string model_file);
	void draw();
};

#endif // SIMPLEMODEL_H
