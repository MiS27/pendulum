#include "world.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>

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

World::World(ShaderProgram* shaderProgram,Model* model): Model(shaderProgram, model)
{

}

bool World::load(string in_config_file, unsigned in_screen_w, unsigned in_screen_h) {
	this->time_last = glutGet(GLUT_ELAPSED_TIME);
	this->angle=0;
	cout<<"World::load after setup_shaders"<<endl;
	ini_t ini(in_config_file, true);
	{
		ini.select("World");
		tilt_sensitivity = ini.get<float>("tiltSensitivity", 0.01f);
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
		shaderProgram->pass_matrix_to_shader("P", P);
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
      ini.get<float>("max_vertical_angle_down", 0.5f),
      1,
      1
		);
	}

	{
		Clock* clock = new Clock(shaderProgram,(Model*)this);
		if(!clock->load()) {
			fprintf(stderr, "Nie ma clocka, nie ma programu.\n");
			return false;
		}
		else
			models.push_back(clock);
	/*
	cout<<"World::load before simpleModel"<<endl;
		SimpleModel* simpleModel = new SimpleModel(shaderProgram,(Model*)this);
	cout<<"World::load before simpleModel->load"<<endl;
		if(!simpleModel->load("models/dobra_dupa.obj")) {
			fprintf(stderr, "Nie ma dup, nie ma programu.\n");
			return false;
		}
		else
			models.push_back(simpleModel);
		*/
	}

	printf("World loaded!\n");
	
  return true;
}

World::~World() {	
	clear();
}

void World::clear() {
	delete camera;
}

void World::draw() {
	calculateM();
	glm::mat4 P = this->P;
	glm::mat4 V = camera->get_view_matrix();
	shaderProgram->pass_matrix_to_shader("V", V);
	
	for (auto &model : models) {
	  model->draw();
	}
}

void World::next_frame (direct_t cam_right_left, direct_t cam_front_back, direct_t cam_up_down, direct_t veh_front_back, direct_t veh_right_left) {
	//camera->move(cam_right_left, cam_front_back, cam_up_down);
	camera->move(cam_front_back);
	camera->tilt(cam_right_left*tilt_sensitivity);
	
    int time_now = glutGet(GLUT_ELAPSED_TIME);
    int time_delta = time_now - time_last;
	time_last = time_now;
	angle=90*time_delta/1000.0;
	//if (angle>360) angle-=360;
	((Clock*)models.back())->gear12->rotate(-15.0/12.0*angle,glm::vec3(0.0f,1.0f,0.0f));
	((Clock*)models.back())->gear15->rotate(angle,glm::vec3(0.0f,1.0f,0.0f));
}

void World::mouse_motion(float dang_h, float dang_v) {
	if (invert_mouse_y) {
		dang_v *= -1;
	}
	camera->mouse_motion(dang_h * mouse_sensitivity_x / 300, dang_v * mouse_sensitivity_y / 300);
}
