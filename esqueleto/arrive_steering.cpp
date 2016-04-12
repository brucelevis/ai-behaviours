#include "stdafx.h"
#include "character.h"
#include "arrive_steering.h"


ArriveSteering::ArriveSteering() {
}


ArriveSteering::~ArriveSteering() {
}

void ArriveSteering::Update(Accelerations &acc, Character * ch, USVec2D target) {
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
}