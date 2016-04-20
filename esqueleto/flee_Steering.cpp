#include "stdafx.h"
#include "character.h"
#include "flee_steering.h"

FleeSteering::FleeSteering() {}

FleeSteering::~FleeSteering() {}

void FleeSteering::Init(Character * ch) {
	Steering::Init(ch);
}

void FleeSteering::Update(Accelerations & acc, USVec2D target) {
	Character * ch = GetCh();
	USVec2D chLoc = ch->GetLoc();
	USVec2D desiredVelocity = (target - chLoc) * -1;
	USVec2D wishAcc = desiredVelocity - ch->GetLinearVelocity();
	float maxAcc = wishAcc.Length();
	wishAcc.Norm();
	acc.linearAcc = wishAcc * maxAcc;
}

void FleeSteering::DrawDebug() {
	Character * ch = GetCh();
}