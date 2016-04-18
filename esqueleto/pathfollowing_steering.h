#ifndef _PATH_FOLLOWING_H_
#define _PATH_FOLLOWING_H_

#include "steering.h"

class PathFollowingSteering: public Steering {
public:
	PathFollowingSteering();
	virtual ~PathFollowingSteering();

	virtual void Update(Accelerations &acc, Character * ch, USVec2D target);
	
	virtual void DrawDebug();
protected:
	
};

#endif //!_PATH_FOLLOWING_H_