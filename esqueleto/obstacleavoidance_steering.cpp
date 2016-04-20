#include <vector>

#include "stdafx.h"
#include "character.h"
#include "obstacleavoidance_steering.h"

ObstacleAvoidanceSteering::ObstacleAvoidanceSteering() {
	
}

ObstacleAvoidanceSteering::~ObstacleAvoidanceSteering() {
}

void ObstacleAvoidanceSteering::Update(Accelerations & acc, Character * ch, USVec2D target) {
	mCh = ch;
}

void ObstacleAvoidanceSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);

	for (std::vector<Obstacle>::iterator obIt = mCh->GetParams().obstacles.begin();
	obIt != mCh->GetParams().obstacles.end(); ++obIt) {
		MOAIDraw::DrawEllipseFill(obIt->x, obIt->y, obIt->r, obIt->r, 64);
	}
}