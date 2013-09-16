#ifndef MODEL_H
#define MODEL_H

#include <string>
#include <vector>
#include <GL/glew.h>
#include "shared.h"
#include "shader_program.h"

using namespace std;

class Model {
protected:
	Model *owner;
	ShaderProgram *shaderProgram;
	glm::mat4 M;
	glm::mat4 calculatedM;
public:
	Model(ShaderProgram *shaderProgram, Model *owner);
	void setM(glm::mat4 M);
	void calculateM();
	void rotate(float angle, glm::vec3 axis);
	void translate(glm::vec3 translationVector);
	virtual ~Model() {};
	
	virtual void draw()=0;
	
};

#endif
