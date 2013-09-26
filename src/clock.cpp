#include "clock.h"
#include <ctime>

Clock::Clock(ShaderProgram *shaderProgram, Model *owner):Model(shaderProgram,owner) {
	t12t6= new Transmission(shaderProgram,(Model*)this);
	t15t6 = new Transmission(shaderProgram,(Model*)this);
	st12t6 = new Transmission(shaderProgram,(Model*)this);
	t36t6 = new Transmission(shaderProgram,(Model*)this,  9 * CLOCK_R + CLOCK_Z - CLOCK_T);
	t60t6 = new Transmission(shaderProgram,(Model*)this);
	t24t6 = new Transmission(shaderProgram,(Model*)this, 5 * CLOCK_R + CLOCK_Z - CLOCK_T);
	t6t6 = new Transmission(shaderProgram, (Model*)this, 9 * CLOCK_R - 0.5 * CLOCK_T);
	t6t6s = new Transmission(shaderProgram, (Model*)this,  7 * CLOCK_R + 0.5 * CLOCK_T);
	//t6t12->rotate(180,glm::vec3(1.0f,0.0f,0.0f));
	t36 = new SimpleModel(shaderProgram,(Model*)this);
	p_t12t6 = new SimpleModel(shaderProgram,(Model*)this);
	p_t15t6 = new SimpleModel(shaderProgram,(Model*)this);
	p_st12t6 = new SimpleModel(shaderProgram,(Model*)this);
	p_t36t6 = new SimpleModel(shaderProgram,(Model*)this);
	p_t60t6 = new SimpleModel(shaderProgram,(Model*)this);
	p_t24t6 = new SimpleModel(shaderProgram,(Model*)this);
	p_t36 = new SimpleModel(shaderProgram,(Model*)this);

	p_t6t6 = new SimpleModel(shaderProgram,(Model*)this);
	p_t6t6s = new SimpleModel(shaderProgram,(Model*)this);
	p_arw = new SimpleModel(shaderProgram,(Model*)this);
	anchor = new SimpleModel(shaderProgram,(Model*)this);

	arw_sec = new SimpleModel(shaderProgram, (Model*)this);
	arw_min = new SimpleModel(shaderProgram, (Model*)this);
	arw_hour = new SimpleModel(shaderProgram, (Model*)this);

	house = new SimpleModel(shaderProgram, (Model*)this);
	house->rotate(-90.0f,glm::vec3(1.0f,0.0f,0.0f));
	house->rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));

	plate = new SimpleModel(shaderProgram, (Model*)this);
	plate->translate(glm::vec3(0.0f,10.0f,-13.5f));
	plate->scale(glm::vec3(0.5f,0.5f,0.5f));

	anchor->translate(glm::vec3(0.0f, -6 * CLOCK_R - 3.5 * CLOCK_T, -0.5 * CLOCK_R + OFFSET - 0.3f));
	anchor->rotate(-90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	anchor->rotate(180.0f, glm::vec3(1.0f, 0.0f, 0.0f));

	t12t6->translate(glm::vec3(0.0f,-6 * CLOCK_R - 3.5 * CLOCK_T, -0.5 * CLOCK_R+OFFSET));
	t15t6->translate(glm::vec3(0.0f, -6 * CLOCK_R - 2.5 * CLOCK_T, 3.0 * CLOCK_R + CLOCK_Z + OFFSET));
	st12t6->translate(glm::vec3(0.0f, -6 * CLOCK_R - 1.5 * CLOCK_T, 0.0f + OFFSET));
	t36t6->translate(glm::vec3(CLOCK_R + 0.5 * CLOCK_T, 0.0f, 0.0f + OFFSET));
	t60t6->translate(glm::vec3(0.0f, 8 * CLOCK_R - CLOCK_T, 0.0f + OFFSET));
	t24t6->translate(glm::vec3(CLOCK_R + 0.5 * CLOCK_T, 12 * CLOCK_R + 0.5 * CLOCK_T, 0.0f + OFFSET));
	t36->translate(glm::vec3(0.0f, 18 * CLOCK_R + 0.5 * CLOCK_T, 0.0f + OFFSET));
	t6t6->translate(glm::vec3(11 * CLOCK_R + CLOCK_Z, -CLOCK_R - 0.5 * CLOCK_T, 0.0f + OFFSET));
	t6t6s->translate(glm::vec3(7 * CLOCK_R + CLOCK_Z, 11 * CLOCK_R, 0.0f + OFFSET));
	// t6t6->rotate(90.0f, glm::vec3(0.0f,0.0f,1.0f));
	// t6t6s->rotate(90.0f, glm::vec3(0.0f,0.0f,1.0f));
	// t12t6->rotate(0.0f,glm::vec3(0.0f,1.0f,0.0f));	
	// t36->rotate(5.0f,glm::vec3(0.0f,1.0f,0.0f));
	t36t6->rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	t24t6->rotate(-90.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	// p_t15t6->translate(glm::vec3(0.805f,0.0f,-5.0f));
	p_t24t6->translate(glm::vec3(CLOCK_R + 0.5 * CLOCK_T, 12 * CLOCK_R + 0.5 * CLOCK_T, 0.0f + OFFSET));
	p_t36t6->translate(glm::vec3(CLOCK_R + 0.5 * CLOCK_T, 0.0f, 0.0f + OFFSET));
	p_t6t6->translate(glm::vec3(11 * CLOCK_R + CLOCK_Z, -CLOCK_R - 0.5 * CLOCK_T, 0.0f+OFFSET));
	p_t6t6s->translate(glm::vec3(7 * CLOCK_R + CLOCK_Z, 11 * CLOCK_R, 0.0f + OFFSET));
	p_arw->translate(glm::vec3(0.0f, -6 * CLOCK_R - 1.5 * CLOCK_T, -13.5f));

	p_t36t6->rotate(-90.0f,glm::vec3(0.0f,0.0f,1.0f));
	p_t24t6->rotate(-90.0f,glm::vec3(0.0f,0.0f,1.0f));

	glm::vec3 pret_scale(0.1f,4.0f,0.1f);
	p_t12t6->scale(pret_scale);
	p_t15t6->scale(pret_scale);
	p_st12t6->scale(pret_scale);
	p_t36t6->scale(glm::vec3(0.1f, 9 * CLOCK_R + CLOCK_Z - CLOCK_T, 0.1f));
	p_t60t6->scale(pret_scale);
	p_t24t6->scale(glm::vec3(0.1f, 5 * CLOCK_R + CLOCK_Z - CLOCK_T, 0.1f));
	p_t36->scale(pret_scale);
	p_arw->scale(glm::vec3(0.1f, 10.0f, 0.1f));
	p_t6t6->scale(glm::vec3(0.1f, 9 * CLOCK_R - 0.5 * CLOCK_T, 0.1f));
	p_t6t6s->scale(glm::vec3(0.1f, 7 * CLOCK_R + 0.5 * CLOCK_T, 0.1f));

	arw_sec->translate(glm::vec3(0.0f,10.3f,-13.5f));
	arw_min->translate(glm::vec3(0.0f,10.4f,-13.5f));
	arw_hour->translate(glm::vec3(0.0f,10.5f,-13.5f));

	arw_sec->scale(glm::vec3(0.25f,0.25f,0.25f));
	arw_min->scale(glm::vec3(0.27f,0.27f,0.27f));
	arw_hour->scale(glm::vec3(0.224f,0.224f,0.224f));

	arw_sec->rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	arw_min->rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	arw_hour->rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));

	arw_sec->rotate(90.0f,glm::vec3(0.0f,0.0f,1.0f));
	arw_min->rotate(90.0f,glm::vec3(0.0f,0.0f,1.0f));
	arw_hour->rotate(90.0f,glm::vec3(0.0f,0.0f,1.0f));

	run(seconds_today());
}

bool Clock::load() {
	return t12t6->load(12,6) && t15t6->load(15,6)
			&& st12t6->load(12,6) && t36t6->load(36,6)
			&& t60t6->load(60,6) && t24t6->load(24,6)
			&& t36->load("models/gear36.obj")
			&& t6t6->load(6,6) && t6t6s->load(6, 6)
			&& arw_sec->load("models/arw_b.obj")
			&& arw_min->load("models/arw_m.obj")
			&& arw_hour->load("models/arw_m.obj")
			&& house->load("models/house.obj")
			&& plate->load("models/clock plate.obj")
			&& anchor->load("models/anchor.obj")

			&& p_t12t6->load("models/pret.obj")
			&& p_t15t6->load("models/pret.obj")
			&& p_st12t6->load("models/pret.obj")
			&& p_t36t6->load("models/pret.obj")
			&& p_t60t6->load("models/pret.obj")
			&& p_t24t6->load("models/pret.obj")
			&& p_t6t6->load("models/pret.obj")
			&& p_t6t6s->load("models/pret.obj")
			&& p_arw->load("models/pret.obj")
			&& p_t36->load("models/pret.obj")
			;
}
void Clock::draw() {
	calculateM();
	t12t6->draw();
	t15t6->draw();
	st12t6->draw();
	t36t6->draw();
	t60t6->draw();
	t24t6->draw();
	t6t6->draw();
	t6t6s->draw();
	t36->draw();

	arw_sec->calculateM();
	arw_sec->draw();
	arw_min->calculateM();
	arw_min->draw();
	arw_hour->calculateM();
	arw_hour->draw();

	house->calculateM();
	house->draw();

	plate->calculateM();
	plate->draw();

	anchor->calculateM();
	anchor->draw();

	// p_t12t6->calculateM();
	// p_t15t6->calculateM();
	// p_st12t6->calculateM();
	p_t36t6->calculateM();
	// p_t60t6->calculateM();
	p_t24t6->calculateM();
	p_t6t6->calculateM();
	p_t6t6s->calculateM();
	// p_t36->calculateM();
	p_arw->calculateM();

	// p_t12t6->draw();
	// p_t15t6->draw();
	// p_st12t6->draw();
	p_t36t6->draw();
	// p_t60t6->draw();
	p_t24t6->draw();
	// p_t36->draw();
	p_arw->draw();
	p_t6t6->draw();
	p_t6t6s->draw();
}
void Clock::run(float dt) {
	float angle = calculate_angle(dt);
	// if(angle>10000000)
	// 	angle = int(angle)%360;
	float ang_t12t6 = -angle/12.0;
	float ang_t15t6 = angle/30;
	float ang_st12t6 = -angle/60;
	float ang_t36t6 = -angle/360;
	float ang_t60t6 = -angle/3600;
	float ang_t24t6 = -angle/3600/4;
	float ang_t36 = -angle/3600/24;
	float ang_t6t6 = angle/360;
	float ang_t6t6s = angle/3600/24;
	float ang_anchor = -angle/12;

	glm::vec3 x_axis(1.0f,0.0f,0.0f);
	glm::vec3 y_axis(0.0f,1.0f,0.0f);
	t12t6->rotate(ang_t12t6,y_axis);
	t15t6->rotate(ang_t15t6,y_axis);
	st12t6->rotate(ang_st12t6,y_axis);
	t36t6->rotate(ang_t36t6,y_axis);
	t60t6->rotate(ang_t60t6,y_axis);
	t24t6->rotate(ang_t24t6,y_axis);
	t36->rotate(ang_t36,y_axis);
	t6t6->rotate(ang_t6t6,y_axis);
	t6t6s->rotate(ang_t6t6s,y_axis);
	anchor->rotate(ang_anchor,y_axis);

	p_t12t6->rotate(ang_t12t6,y_axis);
	p_t15t6->rotate(ang_t15t6,y_axis);
	p_st12t6->rotate(ang_st12t6,y_axis);
	p_t36t6->rotate(ang_t36t6,y_axis);
	p_t60t6->rotate(ang_t60t6,y_axis);
	p_t24t6->rotate(ang_t24t6,y_axis);
	p_t6t6->rotate(ang_t36t6, y_axis);
	p_t6t6s->rotate(ang_t36, y_axis);
	p_t36->rotate(ang_t36,y_axis);

	arw_sec->rotate(ang_st12t6,x_axis);
	arw_min->rotate(ang_t60t6,x_axis);
	arw_hour->rotate(ang_t36,x_axis);
}

int Clock::seconds_today() {
	time_t rawtime;
  struct tm *timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  return timeinfo->tm_sec + 60 * (timeinfo->tm_min + timeinfo->tm_hour * 60);
}

float Clock::calculate_angle(float dt) {
	return dt * 360;
}

Clock::~Clock()
{
	delete t12t6;
	delete t15t6;
	delete st12t6;
	delete t36t6;
	delete t60t6;
	delete t24t6;

	delete t36;
	delete arw_sec;
	delete arw_min;
	delete arw_hour;
}
