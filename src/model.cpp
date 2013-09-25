#include "model.h"

Model::Model(ShaderProgram* shaderProgram, Model *owner) {
	this->shaderProgram = shaderProgram;
	this->owner = owner;
	M=glm::mat4(1.0f);
}


void Model::setM(glm::mat4 M) {
	this->M=M;
}

void Model::calculateM() {
	if(owner)
		calculatedM=owner->calculatedM*M;
	else
		calculatedM=M;
}

void Model::rotate(float angle, glm::vec3 axis) {
	M=glm::rotate(M,angle,axis);
}

void Model::scale(glm::vec3 axis) {
	M=glm::scale(M,axis);
}

void Model::translate(glm::vec3 translationVector)
{
	M=glm::translate(M,translationVector);
}
