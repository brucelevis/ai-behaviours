#include "stdafx.h"
#include "character.h"
#include "aligntomovement_steering.h"
#include "align_steering.h"

#define RAD2DEG 57.2958

AlignToMovementSteering::AlignToMovementSteering() {
	mAlignSteering = new AlignSteering();
}


AlignToMovementSteering::~AlignToMovementSteering() {
}
//45deg of img offset
void AlignToMovementSteering::Update(Accelerations &acc, Character * ch, USVec2D target) {
	mCh = ch;

	USVec2D direction = ch->GetLinearVelocity();
	direction.Norm();

	float wishAngVel = 0;
	if (direction.mX != 0) {
		wishAngVel = atan2f(direction.mY, direction.mX) * RAD2DEG;
	}
	Params &par = ch->GetParams();
	par.target_rotation = wishAngVel;

	mAlignSteering->Update(acc, ch, target);
}

void AlignToMovementSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//LinearAcc
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(mCh->GetLoc(), mCh->GetLoc() * mCh->GetAngularVelocity());

}