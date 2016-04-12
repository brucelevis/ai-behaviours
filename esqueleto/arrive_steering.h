#ifndef _ARRIVE_STEERING_H_
#define _ARRIVE_STEERING_H_

#include "steering.h"

class ArriveSteering: public Steering {
public:
	ArriveSteering();
	virtual ~ArriveSteering();

	virtual void Update(Accelerations &acc, Character * ch, USVec2D target);
private:

};

#endif //!_ARRIVE_STEERING_H_