#ifndef _FLEE_STEERING_H_
#define _FLEE_STEERING_H_

#include "steering.h"

class FleeSteering: public Steering {
public:
	FleeSteering();
	virtual ~FleeSteering();

	void DrawDebug();

	virtual void Update(Accelerations &acc, Character * ch, USVec2D target);
private:
	
};

#endif //!_FLEE_STEERING_H_