#include "stdafx.h"
#include "character.h"
#include "seek_steering.h"

SeekSteering::SeekSteering() {

}


SeekSteering::~SeekSteering() {

}

void SeekSteering::Update(Accelerations &acc, Character * ch, USVec2D target) {
	USVec2D chLoc = ch->GetLoc();
	USVec2D desiredVelocity = target - chLoc;
	USVec2D wishAcc = desiredVelocity - ch->GetLinearVelocity();
	float accFactor = wishAcc.Norm();
	acc.linearAcc = wishAcc * accFactor;
	mLastLinearAcc = acc.linearAcc;
}

void SeekSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//LinearAcc
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(static_cast<USVec2D>(mCh->GetLoc()),
		static_cast<USVec2D>(mCh->GetLoc()) + mLastLinearAcc);

	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);

	MOAIDraw::DrawPoint(mCh->GetParams().target_position);
	MOAIDraw::DrawEllipseOutline(mCh->GetParams().target_position.mX,
		mCh->GetParams().target_position.mY, mCh->GetParams().arrive_radius,
		mCh->GetParams().arrive_radius, 64);
}