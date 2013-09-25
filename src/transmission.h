#ifndef TRANSMISSION_H
#define TRANSMISSION_H
#include "model.h"
#include "simplemodel.h"

class Transmission : public Model
{
public:
	SimpleModel* first;
	SimpleModel* secound;
  float dist;
	Transmission(ShaderProgram *shaderProgram, Model *owner, float dist = 0.1f);
	virtual ~Transmission();
	void draw();
	bool load(int firstGearSize, int secoundGearSize);
};

#endif // TRANSMISSION_H