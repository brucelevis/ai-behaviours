#ifndef __PARAMS_H__
#define __PARAMS_H__

#include <vector>

struct Point {
	float x;
	float y;
};

struct Params {
	USVec2D target_position;
	float max_velocity;
	float max_acceleration;
	float arrive_radius;
	float dest_radius;
	float max_angular_velocity;
	float max_angular_acceleration;
	float angular_dest_radius;
	float angular_arrive_radius;
	float target_rotation;
	float look_ahead;
	std::vector<Point> points;
	uint16_t numSegments;
};


bool ReadParams(const char* filename, Params& params);

#endif