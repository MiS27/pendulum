#ifndef CLOCK_H
#define CLOCK_H
#include "model.h"
#include "simplemodel.h"
#include "transmission.h"

#define t 0.1138f
#define r 0.19612f
#define z 0.10512f

class Clock : public Model
{
public:
	Transmission* t12t6;
	Transmission* t15t6;
	Transmission* st12t6;
	Transmission* t36t6;
	Transmission* t60t6;
	Transmission* t24t6;
	Transmission* t6t6;
	SimpleModel* t36;
	SimpleModel* arw_sec;
	SimpleModel* arw_min;
	SimpleModel* arw_hour;
	SimpleModel* house;
	SimpleModel* plate;
	SimpleModel* p_t12t6;
	SimpleModel* p_t15t6;
	SimpleModel* p_st12t6;
	SimpleModel* p_t36t6;
	SimpleModel* p_t60t6;
	SimpleModel* p_t24t6;
	SimpleModel* p_t36;
	SimpleModel* anchor;
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
