#ifndef _OBSTACLE_AVOIDANCE_H_
#define _OBSTACLE_AVOIDANCE_H_

#include "steering.h"

class ObstacleAvoidanceSteering: public Steering {
public:
	ObstacleAvoidanceSteering();
	virtual ~ObstacleAvoidanceSteering();

	virtual void Update(Accelerations &acc, Character * ch, USVec2D target);

	virtual void DrawDebug();
protected:
	uint16_t mCurrentSegment;
};

#endif //!_OBSTACLE_AVOIDANCE_H_