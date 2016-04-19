#include <vector>

#include "stdafx.h"
#include "character.h"
#include "pathfollowing_steering.h"
#include "seek_steering.h"

PathFollowingSteering::PathFollowingSteering() {
	mSeekDelegate = new SeekSteering();
}

PathFollowingSteering::~PathFollowingSteering() {
}

void PathFollowingSteering::Update(Accelerations & acc, Character * ch, USVec2D target) {
	mCh = ch;

	std::vector<float> distances;
	USVec2D a, b, v, segment;
	float segmentSize, projection;
	//find nearest segment -> number
	for (uint16_t i = 0; i < ch->GetParams().numSegments; ++i) {
		a = USMetaVec2D<float>(ch->GetParams().points[i].x, ch->GetParams().points[i].y);
		b = USMetaVec2D<float>(ch->GetParams().points[i+1].x, ch->GetParams().points[i+1].y);
		v = ch->GetLoc() - a;
		segment = b - a;
		segmentSize = segment.Length();
		projection = v.Dot(segment.NormVector()) + ch->GetParams().look_ahead;
		float distance;
		if (projection > segmentSize) {
			distance = (ch->GetLoc() - b).Length();
		} else if (projection < 0) {
			distance = (ch->GetLoc() - a).Length();
		} else {
			distance = (ch->GetLoc() - (a + (segment.NormVector() * projection))).Length();
		}
		if (distance <= 0.001) {
			distance = 0.f;
		}
		distances.push_back(distance);
	}
	uint16_t nearestPos = 0;
	float nearestValue = *distances.begin();
	for (std::vector<float>::iterator itr = distances.begin(); itr != distances.end(); ++itr) {
		if ((*itr) <= nearestValue) {
			nearestValue = *itr;
			nearestPos = itr - distances.begin();
			mCurrentSegment = nearestPos;
		}
	}

	//calc projection in this segment
	a = USMetaVec2D<float>(ch->GetParams().points[nearestPos].x,
		ch->GetParams().points[nearestPos].y);
	b = USMetaVec2D<float>(ch->GetParams().points[nearestPos + 1].x,
		ch->GetParams().points[nearestPos + 1].y);
	v = ch->GetLoc() - a;
	segment = b - a;
	segmentSize = segment.Length();
	projection = v.Dot(segment.NormVector()) + ch->GetParams().look_ahead;

	if (mCurrentSegment == mCh->GetParams().points.size() - 2) {
		a = USMetaVec2D<float>(ch->GetParams().points[ch->GetParams().points.size() - 2].x,
			ch->GetParams().points[ch->GetParams().points.size() - 2].y);
		b = USMetaVec2D<float>(ch->GetParams().points[ch->GetParams().points.size() - 1].x,
			ch->GetParams().points[ch->GetParams().points.size() - 1].y);
		v = ch->GetLoc() - a;
		segment = b - a;
		segmentSize = segment.Length();
		projection = v.Dot(segment.NormVector()) + ch->GetParams().look_ahead;
	} else if (projection > segmentSize) {
		//float offset = projection - segmentSize;
		a = USMetaVec2D<float>(ch->GetParams().points[nearestPos + 1].x,
			ch->GetParams().points[nearestPos + 1].y);
		b = USMetaVec2D<float>(ch->GetParams().points[nearestPos + 2].x,
			ch->GetParams().points[nearestPos + 2].y);
		v = ch->GetLoc() - a;
		segment = b - a;
		segmentSize = segment.Length();
		projection = v.Dot(segment.NormVector()) + ch->GetParams().look_ahead;
	}

	USVec2D newTarget;

	if (projection > segmentSize) {
		newTarget = b;
	} else if (projection < 0) {
		newTarget = a;
	} else {
		newTarget = a + (segment.NormVector() * projection);
	}

	mTarget = newTarget;
	ch->GetParams().target_position = newTarget;
	mSeekDelegate->Update(acc, ch, newTarget);
}

void PathFollowingSteering::DrawDebug() {
	MOAIGfxDevice& gfxDevice = MOAIGfxDevice::Get();
	gfxDevice.SetPenColor(1.0f, 0.0f, 0.0f, 0.5f);

	//path
	for (uint8_t i = 0; i < mCh->GetParams().numSegments; i++) {
		MOAIDraw::DrawLine(
			USVec2D(mCh->GetParams().points[i].x, mCh->GetParams().points[i].y),
			USVec2D(mCh->GetParams().points[i+1].x, mCh->GetParams().points[i+1].y));
	}

	gfxDevice.SetPenColor(1.0f, 1.0f, 1.0f, 0.5f);
	MOAIDraw::DrawLine(static_cast<USVec2D>(mCh->GetLoc()), mTarget);
}