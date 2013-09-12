#include "world.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>
#include "model.h"

glm::vec3 str_to_vec3(const string &in_s) {
	float x, y,	z;
	printf("in_s: %s\n", in_s.c_str());
	sscanf(in_s.c_str(), " %f / %f / %f", &x, &y, &z);
	return glm::vec3(x, y, z);
}

vector <float> str_to_vec(const string &in_s) {
	float x, y, rotation;
	printf("in_s: %s\n", in_s.c_str());
	sscanf(in_s.c_str(), " %f / %f / %f", &x, &y, &rotation);
	vector <float> result;
	result.push_back(x);
	result.push_back(y);
	result.push_back(rotation);
	return result;
}

bool World::load(string in_config_file, unsigned in_screen_w, unsigned in_screen_h) {
	setup_shaders();
	ini_t ini(in_config_file, true);
	{
		ini.select("World");
		mouse_sensitivity_x = ini.get<float>("mouseSensitivityX", 0.8f);
		mouse_sensitivity_y = ini.get<float>("mouseSensitivityY", 0.8f);
		invert_mouse_y = ini.get<bool>("invertMouseY", false);
	}
	
	{
		ini.select("Projection");
		P = glm::perspective(
			ini.get<float>("fovy", 50.0f),
			ini.get<float>("aspect", (float)in_screen_w / in_screen_h),
			ini.get<float>("zNear", 1.0f),
			ini.get<float>("zFar", 400.0f)
		);
		glMatrixMode(GL_PROJECTION);
		glLoadMatrixf(glm::value_ptr(P));
	}
	
	{
		ini.select("Camera");
		camera = new Camera(
			ini.get<float>("posX", 0.0f),
			ini.get<float>("posY", 0.0f),
			ini.get<float>("posZ", 5.0f),
      ini.get<float>("angX", 0.0f),
			ini.get<float>("speed", 20.0f),
      ini.get<float>("max_vertical_angle_up", 0.5f),
      ini.get<float>("max_vertical_angle_down", 0.5f)
		);
	}

	{
		model = new Model(this);
		if(!model->load("models/dobra_dupa.obj")) {
			fprintf(stderr, "Nie ma dup, nie ma programu.\n");
			return false;
		}
	}

	printf("World loaded!\n");
	
  return true;
}

World::~World() {	
	clear();
}

void World::clear() {
	delete camera;
	clean_shaders();
}

void World::draw() {
	// glm::mat4 V = camera->get_view_matrix();

	// for (unsigned i = 0, len = truck->left_wheels.size(); i < len; ++i) {
	// 	truck->left_wheels[i]->set_mv_matrix(glm::mat4(1.0f));
	// 	truck->right_wheels[i]->set_mv_matrix(glm::mat4(1.0f));
	// }
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glDisable(GL_CULL_FACE);

	// draw();
	
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void World::next_frame (direct_t cam_right_left, direct_t cam_front_back, direct_t cam_up_down, direct_t veh_front_back, direct_t veh_right_left) {
	camera->move(cam_right_left, cam_front_back, cam_up_down);
}

void World::mouse_motion(float dang_h, float dang_v) {
	if (invert_mouse_y) {
		dang_v *= -1;
	}
	camera->mouse_motion(dang_h * mouse_sensitivity_x / 300, dang_v * mouse_sensitivity_y / 300);
}

void World::setup_shaders() {
  shader_program = new ShaderProgram("vshader.txt", NULL, "fshader.txt");
  shader_program->use();
  glUniform1i(shader_program->getUniformLocation("textureMap0"),0);
  glUniform1i(shader_program->getUniformLocation("textureMap1"),1);
}

void World::clean_shaders() {
  delete shader_program;
}

void World::pass_matrix_to_shader(char *var_string, glm::mat4 &matrix) {
	glUniformMatrix4fv(shader_program->getUniformLocation(var_string), 1, false, glm::value_ptr(matrix));	
}

void World::assign_vbo_to_attribute(char* attribute_name, GLuint buf_vbo, int variable_size) {
	GLuint location = shader_program->getAttribLocation(attribute_name);
	glBindBuffer(GL_ARRAY_BUFFER, buf_vbo);
	glEnableVertexAttribArray(location);
	glVertexAttribPointer(location, variable_size, GL_FLOAT, GL_FALSE, 0, NULL);
}
