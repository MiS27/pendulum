#include "clock.h"

Clock::Clock(ShaderProgram *shaderProgram, Model *owner):Model(shaderProgram,owner) {
	t12t6= new Transmission(shaderProgram,(Model*)this);
	t15t6 = new Transmission(shaderProgram,(Model*)this);
	st12t6 = new Transmission(shaderProgram,(Model*)this);
	t36t6 = new Transmission(shaderProgram,(Model*)this);
	t60t6 = new Transmission(shaderProgram,(Model*)this);
	t24t6 = new Transmission(shaderProgram,(Model*)this);
	//t6t12->rotate(180,glm::vec3(1.0f,0.0f,0.0f));
	t15t6->translate(glm::vec3(0.805f,0.11f,0.0f));
	st12t6->translate(glm::vec3(1.5f,0.22f,0.0f));
	st12t6->rotate(180/12,glm::vec3(0.0f,1.0f,0.0f));
	t36t6->translate(glm::vec3(3.0f,0.33f,0.0f));
	t36t6->rotate(2,glm::vec3(0.0f,1.0f,0.0f));
	t60t6->translate(glm::vec3(5.25f,0.44f,0.0f));
	t60t6->rotate(4.5,glm::vec3(0.0f,1.0f,0.0f));
	t24t6->translate(glm::vec3(6.32f,0.55f,0.0f));
	t24t6->rotate(5.1,glm::vec3(0.0f,1.0f,0.0f));
}
bool Clock::load() {
	return t12t6->load(12,6) && t15t6->load(15,6) && st12t6->load(12,6) && t36t6->load(36,6) && t60t6->load(60,6) && t24t6->load(24,6);
}
void Clock::draw() {
	calculateM();
	t12t6->draw();
	t15t6->draw();
	st12t6->draw();
	t36t6->draw();
	t60t6->draw();
	t24t6->draw();
}
void Clock::run(float angle) {
	t12t6->rotate(angle/12.0,glm::vec3(0.0f,1.0f,0.0f));
	t15t6->rotate(-angle/30,glm::vec3(0.0f,1.0f,0.0f));
	st12t6->rotate(angle/60,glm::vec3(0.0f,1.0f,0.0f));
	t36t6->rotate(-angle/360,glm::vec3(0.0f,1.0f,0.0f));
	t60t6->rotate(angle/3600,glm::vec3(0.0f,1.0f,0.0f));
	t24t6->rotate(-angle/3600/4,glm::vec3(0.0f,1.0f,0.0f));
}

Clock::~Clock()
{
	delete t12t6;
	delete t15t6;
	delete t12t6;
	delete t15t6;
	delete st12t6;
	delete t36t6;
	delete t60t6;
	delete t24t6;
}
