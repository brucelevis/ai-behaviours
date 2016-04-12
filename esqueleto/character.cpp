#include <stdafx.h>
#include "steering.h"
#include "arrive_steering.h"
#include "align_steering.h"
#include "flee_steering.h"
#include "seek_steering.h"
#include "character.h"
#include <tinyxml.h>

#include <params.h>

Character::Character(): mLinearVelocity(0.0f, 0.0f), mAngularVelocity(0.0f) {
	RTTI_BEGIN
		RTTI_EXTEND(MOAIEntity2D)
	RTTI_END
}

Character::~Character() {

}

void Character::OnStart() {
	ReadParams("params.xml", mParams);

	//mSteerings.push_back(new SeekSteering());
	//mSteerings.push_back(new FleeSteering());
	//mSteerings.push_back(new ArriveSteering());
	mSteerings.push_back(new AlignSteering());
	mTarget = mParams.targetPosition;
	mArriveRadius = mParams.arrive_radius;
}

void Character::OnStop() {

}

void Character::OnUpdate(float step) {
	Accelerations acc;
	for (std::vector<Steering *>::iterator itr = mSteerings.begin(); itr != mSteerings.end();
	++itr) {
		(*itr)->Update(acc, this, mTarget);
	}

	mLastLinearAcc = acc.linearAcc;
	mLinearVelocity.mX += acc.linearAcc.mX * step;
	mLinearVelocity.mY += acc.linearAcc.mY * step;

	if (mLinearVelocity.mX > mParams.max_velocity)
		mLinearVelocity.mX = mParams.max_velocity;
	if (mLinearVelocity.mX < -mParams.max_velocity)
		mLinearVelocity.mX = -mParams.max_velocity;
	if (mLinearVelocity.mY > mParams.max_velocity)
		mLinearVelocity.mY = mParams.max_velocity;
	if (mLinearVelocity.mY < -mParams.max_velocity)
		mLinearVelocity.mY = -mParams.max_velocity;

	mAngularVelocity += acc.angularAcc * step;

	if (mAngularVelocity > mParams.max_angular_velocity) {

	}

	SetLoc(GetLoc() + static_cast<USVec2D>(mLinearVelocity) * step);
	SetRot(GetRot() + GetAngularVelocity());
}

void Character::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);

	//LinearVel
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(static_cast<USVec2D>(GetLoc()),
		static_cast<USVec2D>(GetLoc()) + mLinearVelocity);

	//LinearAcc
	gfxDevice.SetPenColor(0.0f, 1.0f, 0.0f, 0.5f);
	MOAIDraw::DrawLine(static_cast<USVec2D>(GetLoc()),
		static_cast<USVec2D>(GetLoc()) + mLastLinearAcc);

	//LinearAcc
	gfxDevice.SetPenColor(0.0f, 0.0f, 1.0f, 0.5f);
	MOAIDraw::DrawLine(static_cast<USVec2D>(GetLoc()), mTarget);

	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);

	MOAIDraw::DrawPoint(mTarget);
	MOAIDraw::DrawEllipseOutline(mTarget.mX, mTarget.mY,
		mParams.arrive_radius, mParams.arrive_radius, 64);
}

// Lua configuration
void Character::RegisterLuaFuncs(MOAILuaState& state) {
	MOAIEntity2D::RegisterLuaFuncs(state);

	luaL_Reg regTable[] = {
		{"setLinearVel", _setLinearVel},
		{"setAngularVel", _setAngularVel},
		{NULL, NULL}
	};

	luaL_register(state, 0, regTable);
}

int Character::_setLinearVel(lua_State* L) {
	MOAI_LUA_SETUP(Character, "U")

	float pX = state.GetValue<float>(2, 0.0f);
	float pY = state.GetValue<float>(3, 0.0f);
	self->SetLinearVelocity(pX, pY);
	return 0;
}

int Character::_setAngularVel(lua_State* L) {
	MOAI_LUA_SETUP(Character, "U")

		float angle = state.GetValue<float>(2, 0.0f);
	self->SetAngularVelocity(angle);

	return 0;
}
