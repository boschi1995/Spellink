#pragma once

#define DEG_TO_RAD  0.017453f
#define PI   3.141592593f
#define PI_2 6.283185186f

#define FLOAT_EPSILON 0.001f
#define FLOAT_TO_INT(f1)   static_cast<int>(f1+FLOAT_EPSILON)
#define FFLOAT_EQUAL(f1,f2) (fabs(f1-f2) <= FLOAT_EPSILON)

namespace MY_UTIL
{
	float getDistance(float startX, float statrY, float endX, float endY);
	float getAngle(float startX, float statrY, float endX, float endY);
}
