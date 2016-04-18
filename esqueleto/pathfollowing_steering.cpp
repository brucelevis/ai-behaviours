#include "stdafx.h"
#include "character.h"
#include "pathfollowing_steering.h"
#include "seek_steering.h"

PathFollowingSteering::PathFollowingSteering() {
	mSeekDelegate = new SeekSteering();
}

PathFollowingSteering::~PathFollowingSteering() {
}

void PathFollowingSteering::Update(Accelerations & acc, Character * ch, USVec2D target) {
	mCh = ch;
	USVec2D v = ch->GetLoc() -
		USVec2D(ch->GetParams().points[0].x, ch->GetParams().points[0].y);
	USVec2D segment = USVec2D(ch->GetParams().points[1].x, ch->GetParams().points[1].y) -
		USVec2D(ch->GetParams().points[0].x, ch->GetParams().points[0].y);
	float segmentSize = segment.Length();
	float projection = v.Dot(segment.NormVector()) + ch->GetParams().look_ahead;

	USVec2D newTarget;

	if (projection > segmentSize) {
		newTarget = USVec2D(ch->GetParams().points[1].x, ch->GetParams().points[1].y);
	} else if (projection < 0) {
		newTarget = USVec2D(ch->GetParams().points[0].x, ch->GetParams().points[0].y);
	} else {
		newTarget = USVec2D(ch->GetParams().points[0].x, ch->GetParams().points[0].y) +
			(segment.NormVector() * projection);
	}
	mTarget = newTarget;
	mSeekDelegate->Update(acc, ch, newTarget);
}

void PathFollowingSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);

	//path
	for (uint8_t i = 0; i < mCh->GetParams().numSegments - 1; i++) {
		MOAIDraw::DrawLine(
			USVec2D(mCh->GetParams().points[i].x, mCh->GetParams().points[i].y),
			USVec2D(mCh->GetParams().points[i+1].x, mCh->GetParams().points[i+1].y));
	}
	MOAIDraw::DrawLine(static_cast<USVec2D>(mCh->GetLoc()), mTarget);
}