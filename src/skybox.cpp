#include "skybox.h"
#include "texture.h"


SkyBox::SkyBox(ShaderProgram* shaderProgram,Model* model): Model(shaderProgram, model)
{

}

bool SkyBox::load(string directory, string front, string back, string left, string right, string top, string bottom)
{
	cout<<"SKYBOX"<<endl<<endl;
	Texture* texture = load_texture(directory,front);
	if(texture!=NULL)
		textures.push_back(texture);
	else
		return false;
	Texture* texture2 = load_texture(directory,back);
	if(texture2!=NULL)
		textures.push_back(texture2);
	else
		return false;
	texture = load_texture(directory,left);
	if(texture!=NULL)
		textures.push_back(texture);
	else
		return false;
	texture = load_texture(directory,right);
	if(texture!=NULL)
		textures.push_back(texture);
	else
		return false;
	texture = load_texture(directory,top);
	if(texture!=NULL)
		textures.push_back(texture);
	else
		return false;
	texture = load_texture(directory,bottom);
	if(texture!=NULL)
		textures.push_back(texture);
	else
		return false;
	size=24;
	float a=1000.0f;
	glm::vec3 pos_data_vec[24] = 
	{
		// Front face
		glm::vec3(a/2, a, a/2), glm::vec3(a/2, 0.0f, a/2), glm::vec3(-a/2, a, a/2), glm::vec3(-a/2, 0.0f, a/2),
		// Back face
		glm::vec3(-a/2, a, -a/2), glm::vec3(-a/2, 0.0f, -a/2), glm::vec3(a/2, a, -a/2), glm::vec3(a/2, 0.0f, -a/2),
		// Left face
		glm::vec3(-a/2, a, a/2), glm::vec3(-a/2, 0.0f, a/2), glm::vec3(-a/2, a, -a/2), glm::vec3(-a/2, 0.0f, -a/2),
		// Right face
		glm::vec3(a/2, a, -a/2), glm::vec3(a/2, 0.0f, -a/2), glm::vec3(a/2, a, a/2), glm::vec3(a/2, 0.0f, a/2),
		// Top face
		glm::vec3(-a/2, a, -a/2), glm::vec3(a/2, a, -a/2), glm::vec3(-a/2, a, a/2), glm::vec3(a/2, a, a/2),
		// Bottom face
		glm::vec3(a/2, 0.0f, -a/2), glm::vec3(-a/2, 0.0f, -a/2), glm::vec3(a/2, 0.0f, a/2), glm::vec3(-a/2, 0.0f, a/2),
	};
	glm::vec2 tex_coords_vec[4] =
	{
		glm::vec2(0.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f), glm::vec2(1.0f, 0.0f)
	};

	glm::vec3 norm_data_vec[6] = 
	{
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	pos_data = (float*)calloc(sizeof(float) * 3, size);
	norm_data = (float*)calloc(sizeof(float) * 3, size);
	tex_coords = (float*)calloc(sizeof(float) * 2, size);
	for (int i=0; i<24;i++) {
		 int i3=3*i;
		 pos_data[i3]=pos_data_vec[i].x;
		 pos_data[i3+1]=pos_data_vec[i].y;
		 pos_data[i3+2]=pos_data_vec[i].z;
		 //pos_data[i++]=1.0f;
		 norm_data[i3]=norm_data_vec[i/4].x;
		 norm_data[i3+1]=norm_data_vec[i/4].y;
		 norm_data[i3+2]=norm_data_vec[i/4].z;
		 //norm_data[i++]=0.0f;
		 int i2=2*i;
		 tex_coords[i2]=tex_coords_vec[i%4].x;
		 tex_coords[i2+1]=tex_coords_vec[i%4].y;
	}
	cout<<pos_data[70]<<" "<<norm_data[18]<<endl;
	init_vbo();
	cout<<"vbo"<<endl;
	init_vao();
	cout<<"vao"<<endl;
	return true;
}
SkyBox::~SkyBox() {
	for (Texture* texture : textures) {
		delete texture;
	}
	
	textures.clear();
	free_vao();
	free_vbo();
}

Texture* SkyBox::load_texture(string directory, string file) {
	if(directory.back()!='/')
		directory+='/';
	Texture *texture = new Texture(GL_TEXTURE_2D, string(directory+file).c_str());
	if (!texture->load()) {
		cout<<"Error loading texture " <<directory+file<<endl;
		delete texture;
		texture = new Texture(GL_TEXTURE_2D, "./models/blank.png");
		if(texture->load())
		  return texture;
		else
			return NULL;
	} else {
		cout<<"Loaded texture " <<directory+file<<endl;
		return texture;
	}
}

GLuint SkyBox::make_buffer(void *data, int vertex_size) {
	GLuint handle;

	glGenBuffers(1,&handle);
	glBindBuffer(GL_ARRAY_BUFFER, handle);
	glBufferData(GL_ARRAY_BUFFER, size * vertex_size, data, GL_STATIC_DRAW);

	return handle;
}

void SkyBox::init_vbo() {
	bufVertices = make_buffer(pos_data, sizeof(float) * 3);
	bufNormals = make_buffer(norm_data, sizeof(float) * 3);
	bufTexCoords = make_buffer(tex_coords, sizeof(float) * 2);
}

void SkyBox::init_vao() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	shaderProgram->assign_vbo_to_attribute("vertex", bufVertices, 3);
	shaderProgram->assign_vbo_to_attribute("normal", bufNormals, 3);
	shaderProgram->assign_vbo_to_attribute("texCoords0", bufTexCoords, 2);

	glBindVertexArray(0);
}
void SkyBox::free_vbo() {
	glDeleteBuffers(1, &bufVertices);
	glDeleteBuffers(1, &bufNormals);
	glDeleteBuffers(1, &bufTexCoords);
}

void SkyBox::free_vao() {
	glDeleteVertexArrays(1, &vao);
}
void SkyBox::draw() {
	calculateM();
	shaderProgram->pass_matrix_to_shader("M", calculatedM);
   glDepthMask(0); 
   glBindVertexArray(vao); 
   int i=0;
   for (Texture* texture : textures) 
   { 
      texture->bind(); 	
      
      glDrawArrays(GL_TRIANGLE_STRIP, i*4, 4); 
      i++;
   } 
   glDepthMask(1); 
}
