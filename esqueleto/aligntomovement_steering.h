#ifndef _ALIGNTOMOVEMENT_STEERING_H_
#define _ALIGNTOMOVEMENT_STEERING_H_

#include "steering.h"

class AlignSteering;

class AlignToMovementSteering: public Steering {
public:
	AlignToMovementSteering();
	virtual ~AlignToMovementSteering();

	virtual void DrawDebug();

	virtual void Update(Accelerations &acc, Character * ch, USVec2D target);
private:
	AlignSteering * mAlignSteering;
};

#endif //!_ALIGNTOMOVEMENT_STEERING_H_