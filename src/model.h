#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include "shared.h"

class World;
#include "mesh.h"
#include "texture.h"
#include "vertex.h"

using namespace std;

class Model {
protected:
	vector <Mesh*> meshes;
	vector <Texture*> textures;
	World *world;
	
	virtual bool parse_scene(const aiScene *pScene, string &model_file);
	bool load_textures(const aiScene* pScene, const string &model_file);
	bool load_texture_from_material(aiMaterial *material, string &dir, Texture **texture);
public:
	Model(World *in_world);
	virtual ~Model();
	virtual void clear();
	bool load(string model_file);
	
	void draw();
};

#endif
