#ifndef __PARAMS_H__
#define __PARAMS_H__

struct Params {
	USVec2D targetPosition;
	float max_velocity;
	float max_acceleration;
	float arrive_radius;
	float dest_radius;
	float max_angular_velocity;
};

bool ReadParams(const char* filename, Params& params);

#endif