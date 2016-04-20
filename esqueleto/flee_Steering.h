#ifndef _FLEE_STEERING_H_
#define _FLEE_STEERING_H_

#include "steering.h"

class FleeSteering: public Steering {
public:
	FleeSteering();
	virtual ~FleeSteering();

	virtual void Init(Character * ch);

	void DrawDebug();

	virtual void Update(Accelerations &acc, USVec2D target);
private:
};

#endif //!_FLEE_STEERING_H_