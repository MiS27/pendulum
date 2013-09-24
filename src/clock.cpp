#include "clock.h"

Clock::Clock(ShaderProgram *shaderProgram, Model *owner):Model(shaderProgram,owner) {
	t12t6= new Transmission(shaderProgram,(Model*)this);
	t15t6 = new Transmission(shaderProgram,(Model*)this);
	st12t6 = new Transmission(shaderProgram,(Model*)this);
	t36t6 = new Transmission(shaderProgram,(Model*)this);
	t60t6 = new Transmission(shaderProgram,(Model*)this);
	t24t6 = new Transmission(shaderProgram,(Model*)this);
	//t6t12->rotate(180,glm::vec3(1.0f,0.0f,0.0f));
	t36 = new SimpleModel(shaderProgram,(Model*)this);
	arw_sec = new SimpleModel(shaderProgram, (Model*)this);
	arw_min = new SimpleModel(shaderProgram, (Model*)this);
	arw_hour = new SimpleModel(shaderProgram, (Model*)this);

	t12t6->rotate(30.0f,glm::vec3(0.0f,1.0f,0.0f));	
	t15t6->translate(glm::vec3(0.805f,0.11f,0.0f));
	st12t6->translate(glm::vec3(1.5f,0.22f,0.0f));
	//st12t6->rotate(180/12,glm::vec3(0.0f,1.0f,0.0f));
	t36t6->translate(glm::vec3(3.0f,0.33f,0.0f));
	//t36t6->rotate(2,glm::vec3(0.0f,1.0f,0.0f));
	t60t6->translate(glm::vec3(5.25f,0.44f,0.0f));
	//t60t6->rotate(4.5,glm::vec3(0.0f,1.0f,0.0f));
	t24t6->translate(glm::vec3(6.34f,0.55f,0.0f));
	//t24t6->rotate(5.1,glm::vec3(0.0f,1.0f,0.0f));
	t36->translate(glm::vec3(7.89f, 0.66f, 0.0f));
	t36->rotate(5.0f,glm::vec3(0.0f,1.0f,0.0f));

	arw_sec->rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	arw_min->rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));
	arw_hour->rotate(-90.0f,glm::vec3(0.0f,1.0f,0.0f));

	arw_sec->rotate(90.0f,glm::vec3(0.0f,0.0f,1.0f));
	arw_min->rotate(90.0f,glm::vec3(0.0f,0.0f,1.0f));
	arw_hour->rotate(90.0f,glm::vec3(0.0f,0.0f,1.0f));
	
}
bool Clock::load() {
	return t12t6->load(12,6) && t15t6->load(15,6)
			&& st12t6->load(12,6) && t36t6->load(36,6)
			&& t60t6->load(60,6) && t24t6->load(24,6)
			&& t36->load("models/gear36.obj")
			&& arw_sec->load("models/arw_b.obj")
			&& arw_min->load("models/arw_m.obj")
			&& arw_hour->load("models/arw_m.obj");
}
void Clock::draw() {
	calculateM();
	t12t6->draw();
	t15t6->draw();
	st12t6->draw();
	t36t6->draw();
	t60t6->draw();
	t24t6->draw();
	t36->calculateM();
	t36->draw();

	arw_sec->calculateM();
	arw_sec->draw();
	arw_min->calculateM();
	arw_min->draw();
	arw_hour->calculateM();
	arw_hour->draw();
}
void Clock::run(float angle) {
	t12t6->rotate(angle/12.0,glm::vec3(0.0f,1.0f,0.0f));
	t15t6->rotate(-angle/30,glm::vec3(0.0f,1.0f,0.0f));
	st12t6->rotate(angle/60,glm::vec3(0.0f,1.0f,0.0f));
	t36t6->rotate(-angle/360,glm::vec3(0.0f,1.0f,0.0f));
	t60t6->rotate(angle/3600,glm::vec3(0.0f,1.0f,0.0f));
	t24t6->rotate(-angle/3600/4,glm::vec3(0.0f,1.0f,0.0f));
	t36->rotate(angle/3600/24,glm::vec3(0.0f,1.0,0.0f));

	arw_sec->rotate(-angle/60,glm::vec3(1.0f,0.0,0.0f));
	arw_min->rotate(-angle/3600,glm::vec3(1.0f,0.0,0.0f));
	arw_hour->rotate(-angle/3600/24,glm::vec3(1.0f,0.0f,0.0f));
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
