#ifndef SEGMENT_H
#define SEGMENT_H
#include "stdlib.h"

class Segment
{

public:
	// constructeurs
	Segment() : d_x{ 0 }, d_y{ 0 }, d_z{ 0 } {}
	Segment(float x, float y, float z) : d_x{ x }, d_y{ y }, d_z{ z } {}
	// accesseurs
	float x() const { return d_x; }
	float y() const { return d_y; }
	float z() const { return d_z; }


private:
	// coordonnées
	float d_x, d_y, d_z;
};

#endif
