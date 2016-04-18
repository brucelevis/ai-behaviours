#include "stdafx.h"
#include "character.h"
#include "arrive_steering.h"


ArriveSteering::ArriveSteering() {
}


ArriveSteering::~ArriveSteering() {
}

void ArriveSteering::Update(Accelerations &acc, Character * ch, USVec2D target) {
	mCh = ch;
	USVec2D chLoc = ch->GetLoc();
	USVec2D desiredVelocity = target - chLoc;
	float arriveFactor = desiredVelocity.Length();
	if (arriveFactor < ch->GetArriveRadius()) {
		desiredVelocity.Norm();
		desiredVelocity = desiredVelocity *
			ch->GetParams().max_velocity * (arriveFactor / ch->GetArriveRadius());
		USVec2D wishAcc = desiredVelocity - ch->GetLinearVelocity();
		float accFactor = wishAcc.Norm();
		acc.linearAcc = wishAcc * accFactor * ch->GetParams().max_acceleration;
	} else {
		USVec2D wishAcc = desiredVelocity - ch->GetLinearVelocity();
		float accFactor = wishAcc.Norm();
		acc.linearAcc = wishAcc * accFactor * ch->GetParams().max_acceleration;
	}
	mLastLinearAcc = acc.linearAcc;
}

void ArriveSteering::DrawDebug() {
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