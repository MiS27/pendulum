#ifndef CLOCK_H
#define CLOCK_H
#include "model.h"
#include "simplemodel.h"
#include "transmission.h"

class Clock : public Model
{
public:
	Transmission* t12t6;
	Transmission* t15t6;
	Transmission* st12t6;
	Transmission* t36t6;
	Transmission* t60t6;
	Transmission* t24t6;
	SimpleModel* t36;
	SimpleModel* arw_sec;
	SimpleModel* arw_min;
	SimpleModel* arw_hour;
	Clock(ShaderProgram *shaderProgram, Model *owner);
	virtual ~Clock();
	void draw();
	bool load();
	void run(float dt);
private:
	float calculate_angle(float dt);
	int seconds_today();
};

#endif // CLOCK_H
