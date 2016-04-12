#include "stdafx.h"
#include "character.h"
#include "flee_steering.h"

FleeSteering::FleeSteering() {
}


FleeSteering::~FleeSteering() {
}

void FleeSteering::Update(Accelerations & acc, Character * ch, USVec2D target) {
	USVec2D chLoc = ch->GetLoc();
	USVec2D desiredVelocity = (target - chLoc) * -1;
	USVec2D wishAcc = desiredVelocity - ch->GetLinearVelocity();
	float maxAcc = wishAcc.Length();
	wishAcc.Norm();
	acc.linearAcc = wishAcc * maxAcc;
}