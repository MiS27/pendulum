#include "mesh.h"
#include <vector>

using namespace std;

Mesh::Mesh (const aiMesh *paiMesh, Texture *texture, ShaderProgram *shaderProgram) {
	this->texture = texture;
	this->shaderProgram = shaderProgram;
	
	vector <unsigned> indices;
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
	
	for (unsigned i = 0; i < paiMesh->mNumFaces; ++i) {
		const aiFace& Face = paiMesh->mFaces[i];
		if (Face.mNumIndices == 3) {
			indices.push_back(Face.mIndices[0]);
			indices.push_back(Face.mIndices[1]);
			indices.push_back(Face.mIndices[2]);
		}
	}
	
	size = indices.size();
	pos_data = (float*)calloc(sizeof(float) * 4, size);
	norm_data = (float*)calloc(sizeof(float) * 4, size);
	tex_coords = (float*)calloc(sizeof(float) * 2, size);
	
	for (unsigned i = 0, v = indices[i]; i < size;	++i, v = indices[i]) {
		const aiVector3D* tex_coord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][v]) : &Zero3D;
		const aiVector3D* pos = &(paiMesh->mVertices[v]);
		const aiVector3D* norm = &(paiMesh->mNormals[v]);

		unsigned i4 = i << 1;
		tex_coords[i4] = tex_coord->x;
		tex_coords[i4 + 1] = tex_coord->y;

		i4 <<= 1;
		pos_data[i4] = pos->x;
		pos_data[i4 + 1] = pos->y;
		pos_data[i4 + 2] = pos->z;
		pos_data[i4 + 3] = 1.0f;
		
		norm_data[i4] = norm->x;
		norm_data[i4 + 1] = norm->y;
		norm_data[i4 + 2] = norm->z;
		norm_data[i4 + 3] = 0.0f;
	}
	//cout<<"Mesh::Mesh before init_vbo"<<endl;
	init_vbo();
	//cout<<"Mesh::Mesh before init_vao"<<endl;
	init_vao();
	//cout<<"Mesh::Mesh after init_vao"<<endl;
}

Mesh::~Mesh() {
	free_vao();
	free_vbo();
	delete pos_data;
	delete norm_data;
	delete tex_coords;
	pos_data = NULL;
	norm_data = NULL;
	tex_coords = NULL;
	texture = NULL;
}

void Mesh::draw() {
	texture->bind();
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, size);
	glBindVertexArray(0);
}

GLuint Mesh::make_buffer(void *data, int vertex_size) {
	GLuint handle;

	glGenBuffers(1,&handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, size * vertex_size, data, GL_STATIC_DRAW);

	return handle;
}

void Mesh::init_vbo() {
	bufVertices = make_buffer(pos_data, sizeof(float) * 4);
	bufNormals = make_buffer(norm_data, sizeof(float) * 4);
	bufTexCoords = make_buffer(tex_coords, sizeof(float) * 2);
}


void Mesh::init_vao() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	//cout<<"Mesh::init_vao before shaderProgram "<<shaderProgram<<endl;
	shaderProgram->assign_vbo_to_attribute("vertex", bufVertices, 4);
	shaderProgram->assign_vbo_to_attribute("normal", bufNormals, 4);
	shaderProgram->assign_vbo_to_attribute("texCoords0", bufTexCoords, 2);

	glBindVertexArray(0);
}

void Mesh::free_vbo() {
	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufNormals);
	glDeleteBuffers(1, &bufTexCoords);
}

void Mesh::free_vao() {
	glDeleteVertexArrays(1, &vao);
}
