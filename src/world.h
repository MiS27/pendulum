#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <algorithm>

#include "shared.h"
#include "model.h"

class World;

#include "shader_program.h"

class Camera;
#include "camera.h"

using namespace std;

class World {
private: 
	ShaderProgram *shader_program;
	glm::mat4 P;
	float mouse_sensitivity_x, mouse_sensitivity_y;
	bool invert_mouse_y;

	Camera *camera;

	void setup_shaders();
	void clean_shaders();
public:
	World(){}
	~World();
	void clear();
	void next_frame(direct_t keys_h, direct_t keys_v, direct_t height, direct_t vehicle, direct_t v_turn);
	bool load(string in_config_file, unsigned in_screen_w, unsigned in_screen_h);

	void draw();
	void mouse_motion(float dang_h, float dang_v);

	void pass_matrix_to_shader(const char *var_string, glm::mat4 &matrix);
	void assign_vbo_to_attribute(char* attribute_name, GLuint buf_vbo, int variable_size);
};

#endif
