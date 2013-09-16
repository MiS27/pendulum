#ifndef CLOCK_H
#define CLOCK_H
#include "model.h"
#include "simplemodel.h"

class Clock : public Model
{
public:
	SimpleModel* gear12;
	SimpleModel* gear15;
	Clock(ShaderProgram *shaderProgram, Model *owner);
	virtual ~Clock();
	void draw();
	bool load();
};

#endif // CLOCK_H
