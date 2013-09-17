#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "shared.h"
#include "model.h"
#include "simplemodel.h"
#include "clock.h"

#include "shader_program.h"

class Camera;
#include "camera.h"


class World : public Model {
private: 
	float mouse_sensitivity_x, mouse_sensitivity_y;
	float tilt_sensitivity;
	bool invert_mouse_y;
	float angle;
	int time_last;

public:
	World(ShaderProgram* shaderprogram, Model* owner);
	~World();
	Camera *camera;
	vector<Model*> models;
	glm::mat4 P;
	void clear();
	void next_frame(direct_t keys_h, direct_t keys_v, direct_t height, direct_t vehicle, direct_t v_turn);
	bool load(string in_config_file, unsigned in_screen_w, unsigned in_screen_h);

	void draw();
	void mouse_motion(float dang_h, float dang_v);

};

#endif
