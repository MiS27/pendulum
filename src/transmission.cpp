#include "transmission.h"

Transmission::Transmission(ShaderProgram* shaderProgram, Model* owner, float dist): Model(shaderProgram, owner) {
	first=new SimpleModel(shaderProgram,(Model*)this);
	secound=new SimpleModel(shaderProgram,(Model*)this);
	this->dist = dist;
}
bool Transmission::load(int firstGearSize, int secoundGearSize) {
	ostringstream firstStream;
	firstStream << firstGearSize;
	if(!first->load("models/gear"+firstStream.str()+".obj")) {
		fprintf(stderr, "Nie ma kół, nie ma programu.\n");
		return false;
	}
	
	first->rotate(180/firstGearSize,glm::vec3(0.0f,1.0f,0.0f));
	ostringstream secoundStream;
	secoundStream << secoundGearSize;
	if(!secound->load("models/gear"+secoundStream.str()+".obj")) {
		fprintf(stderr, "Nie ma kół, nie ma programu.\n");
		return false;
	}
	secound->translate(glm::vec3(0.0f,dist,0.0f));
	return true;
}
void Transmission::draw() {
	calculateM();
	first->draw();
	secound->draw();
}
Transmission::~Transmission()
{
	delete first;
	delete secound;
}