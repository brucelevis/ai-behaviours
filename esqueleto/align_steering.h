#ifndef _ALIGN_STEERING_H_
#define _ALIGN_STEERING_H_

#include "steering.h"

class AlignSteering: public Steering {
public:
	AlignSteering();
	virtual ~AlignSteering();

	virtual void DrawDebug();

	virtual void Update(Accelerations &acc, Character * ch, USVec2D target);
private:
	
};

#endif //!_ALIGN_STEERING_H_