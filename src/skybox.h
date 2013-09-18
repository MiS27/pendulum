#ifndef SKYBOX_H
#define SKYBOX_H
#include "model.h"
#include "shared.h"
#include "shader_program.h"
#include "texture.h"
#include <vector>

class SkyBox : public Model
{
private: 
	float *pos_data, *norm_data, *tex_coords;
	unsigned size;
	GLuint vao, bufVertices, bufNormals, bufTexCoords;
	void init_vao();
	void init_vbo();
	void free_vao();
	void free_vbo();
	vector <Texture*> textures;
	Texture* load_texture(string directory, string file);
	GLuint make_buffer(void *data, int vertex_size);
public: 
	SkyBox(ShaderProgram* shaderProgram, Model* owner);
	virtual ~SkyBox();
	bool load(string directory, string front, string back, string left, string right, string top, string bottom); 
	void draw(); 
};

#endif // SKYBOX_H
