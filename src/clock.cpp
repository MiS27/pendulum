#include "clock.h"

Clock::Clock(ShaderProgram *shaderProgram, Model *owner):Model(shaderProgram,owner) {
	gear12=new SimpleModel(shaderProgram,(Model*)this);
	gear12->translate(glm::vec3(10.0f,0,0));
	gear15=new SimpleModel(shaderProgram,(Model*)this);
}
bool Clock::load() {
	if(!gear12->load("models/gear12.obj")) {
		fprintf(stderr, "Nie ma kół, nie ma programu.\n");
		return false;
	}
	if(!gear15->load("models/gear15.obj")) {
		fprintf(stderr, "Nie ma kół, nie ma programu.\n");
		return false;
	}
	return true;
}
void Clock::draw() {
	calculateM();
	gear12->draw();
	gear15->draw();
}
Clock::~Clock()
{
	delete gear12;
	delete gear15;
}
