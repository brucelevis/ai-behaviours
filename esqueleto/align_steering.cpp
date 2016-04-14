#include "stdafx.h"
#include "character.h"
#include "align_steering.h"

AlignSteering::AlignSteering() {
}


AlignSteering::~AlignSteering() {
}
//45deg of img offset
void AlignSteering::Update(Accelerations &acc, Character * ch, USVec2D target) {
	mCh = ch;
	/* P4 */
	/*USVec2D targetVec = (target - ch->GetLoc());
	float targetRot = targetVec.mX / (sqrt(pow(targetVec.mX, 2) + pow(targetVec.mY, 2)));
	//targetRot = (ch->GetLoc().Dot(target)) / (ch->GetLoc().Norm() * target.Norm());
	targetRot = atan2f(target.mY - ch->GetLoc().mY, target.mX - ch->GetLoc().mX);*/
	float currentRot = ch->GetRot();
	float wishAngVel = currentRot - ch->GetParams().target_rotation;
	float wishAngAcc = ch->GetAngularVelocity() - wishAngVel;
	acc.angularAcc = wishAngAcc;
}

void AlignSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//LinearAcc
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(mCh->GetLoc(), mCh->GetLoc() * mCh->GetAngularVelocity());

}