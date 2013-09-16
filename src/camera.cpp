#include "camera.h"
#include <math.h>

#include "shared.h"

Camera::Camera(float position_x, float position_y, float position_z, float angle_horizontal, float speed, float max_vertical_angle_up, float max_vertical_angle_down, float max_tilt_angle_left, float max_tilt_angle_right) : position(position_x, position_y, position_z) {
	this->angle_horizontal = angle_horizontal;
	this->angle_vertical = 0;
	this->angle_tilt = 0;

    this->max_vertical_angle_up = PI / 2 * max_vertical_angle_up;
    this->max_vertical_angle_down = PI / 2 * max_vertical_angle_down;
    this->max_tilt_angle_left = PI / 2 * max_tilt_angle_left;
    this->max_tilt_angle_right = PI / 2 * max_tilt_angle_right;

    this->speed = speed / 1000;
	this->time_last = glutGet(GLUT_ELAPSED_TIME);
}

void Camera::mouse_motion(float angle_horizontal_delta, float angle_vertical_delta) {
    angle_horizontal = normalize_angle(angle_horizontal - angle_horizontal_delta);
    angle_vertical = max(min(angle_vertical - angle_vertical_delta, max_vertical_angle_up), -max_vertical_angle_down);
}

void Camera::tilt(float angle_tilt_delta) {
    angle_tilt = max(min(angle_tilt - angle_tilt_delta, max_tilt_angle_right), -max_tilt_angle_left);

}

void Camera::move(direct_t right_left, direct_t front_back, direct_t up_down) {
    int time_now = glutGet(GLUT_ELAPSED_TIME);
    int time_delta = time_now - time_last;
	time_last = time_now;

	float speed_delta = speed * time_delta;
	float sinus = sin(angle_horizontal);
    float cosinus = cos(angle_horizontal);

	position = Vertex3D<float>(
        position.x + speed_delta * (front_back  * sinus + right_left * cosinus),
        position.y + speed_delta * (front_back * cosinus - right_left * sinus),
        max(1.1f, position.z + speed_delta * up_down)
    );
}

void Camera::move(direct_t front_back) {
    int time_now = glutGet(GLUT_ELAPSED_TIME);
    int time_delta = time_now - time_last;
	time_last = time_now;

	float speed_delta = speed * time_delta;

	position = Vertex3D<float>(
        position.x + speed_delta * front_back * cos(angle_vertical) * sin(angle_horizontal),
        position.y + speed_delta * front_back * cos(angle_vertical) * cos(angle_horizontal),
        position.z + speed_delta * front_back * sin(angle_vertical)
    );
}

glm::mat4 Camera::get_view_matrix() {
    float ang_v = angle_vertical;
    float ang_h = angle_horizontal;
    float xy = CAMERA_RADIUS * cos(ang_v);
    float o_xz = -sin(ang_v);
    float sin_h = sin(ang_h);
    float cos_h = cos(ang_h);
    float sin_t = sin(angle_tilt);
    float cos_t = cos(angle_tilt);
    //cout<<"angle_tilt "<<angle_tilt<<" sin_t "<<sin_t<<" cos_t "<<cos_t<<endl;
	return glm::lookAt(
		glm::vec3(position.x, position.z, position.y),
		glm::vec3(position.x + xy * sin_h, position.z + CAMERA_RADIUS * sin(ang_v), position.y + xy * cos_h),
		//glm::vec3(o_xz * sin_h, cos(ang_v), o_xz * cos_h)
		glm::vec3(sin_t,cos_t,0)
	);
}
