#ifndef MESH_H
#define MESH_H

#include "shared.h"
class Mesh;
#include "shader_program.h"

#include "texture.h"
#include <vector>

using namespace std;

class Mesh {
private:
	float *pos_data, *norm_data, *tex_coords;
	unsigned size;
	GLuint vao, bufVertices, bufNormals, bufTexCoords;
	Texture *texture;
	
	ShaderProgram *shaderProgram;
	glm::mat4 M;
	GLuint make_buffer(void *data, int vertex_size);
	void init_vbo();
	void init_vao();
	void free_vbo();
	void free_vao();
public:
	Mesh(const aiMesh *paiMesh, Texture *in_texture, ShaderProgram *shaderProgram);
	~Mesh();

	void draw();
	
	void set_m_matrix(glm::mat4 in_M);
};

#endif
