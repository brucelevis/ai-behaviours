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
}