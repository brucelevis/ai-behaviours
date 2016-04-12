#ifndef _SEEK_STEERING_H_
#define _SEEK_STEERING_H_

#include "steering.h"

class SeekSteering:	public Steering {
public:
	SeekSteering();
	virtual ~SeekSteering();

	virtual void Update(Accelerations &acc, Character * ch, USVec2D target);
private:

};

#endif //!_SEEK_STEERING_H_