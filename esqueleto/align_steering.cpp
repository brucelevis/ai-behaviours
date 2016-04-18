#include "stdafx.h"
#include "character.h"
#include "align_steering.h"

#define RAD2DEG 57.2958

AlignSteering::AlignSteering() {
}


AlignSteering::~AlignSteering() {
}
//45deg of img offset
void AlignSteering::Update(Accelerations &acc, Character * ch, USVec2D target) {
	mCh = ch;
	float currentRot = ch->GetRot();
	float wishAngVel = ch->GetParams().target_rotation - currentRot;
	
	//wrap -180, 180
	if (wishAngVel < -180) {
		wishAngVel += 360;
	} else if (wishAngVel > 180) {
		wishAngVel -= 360;
	}

	float wishAngAcc = wishAngVel - ch->GetAngularVelocity();
	acc.angularAcc = ch->GetParams().max_angular_acceleration * wishAngAcc;
}

void AlignSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//LinearAcc
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(mCh->GetLoc(), mCh->GetLoc() * mCh->GetAngularVelocity());

}