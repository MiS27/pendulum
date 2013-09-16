#ifndef CAMERA_H
#define CAMERA_H
#include <stdlib.h>
#include <cmath>

#include "shared.h"
#include "vertex.h"

#define CAMERA_RADIUS 100

class Camera {
private:
	Vertex3D<float>position;
	float angle_horizontal, angle_vertical, angle_tilt;
    float max_vertical_angle_up, max_vertical_angle_down;
    float max_tilt_angle_left, max_tilt_angle_right;
    float speed;
	int time_last;
public:
    Camera(float position_x, float position_y, float position_z, float angle_horizontal, float speed, float max_vertical_angle_up, float max_vertical_angle_down, float max_tilt_angle_left, float max_tilt_angle_right);
    void mouse_motion(float angle_horizontal_delta, float angle_vertical_delta);
    void tilt(float angle_tilt_delta);
	void move(direct_t right_left, direct_t front_back, direct_t up_down);
	void move(direct_t front_back);
	glm::mat4 get_view_matrix();
    void animate_crash();
};

#endif
