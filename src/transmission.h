#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#include "model.h"
#include "simplemodel.h"

class Transmission : public Model
{
public:
	SimpleModel* first;
	SimpleModel* secound;
	Transmission(ShaderProgram *shaderProgram, Model *owner);
	virtual ~Transmission();
	void draw();
	bool load(int firstGearSize, int secoundGearSize);
};

#endif // TRANSMISSION_H