#include "Interpolator.h"
#include <cmath>

#define PI (3.14159f)
float LinearInterpolator::calc(float f)
{
	return f;
}

float AccelerateInterpolator::calc(float f)
{
	return f * f;
}

float DecelerateInterpolator::calc(float f)
{
	return (1.0f - (1.0f - f) * (1.0f - f));
}

float CycleInterpolator::calc(float f)
{
	return sin(2 * PI * f);
}

float AccelerateDecelerateInterpolator::calc(float f)
{
	return (cos((f + 1.0f) * PI / 2.0f) + 0.5f);
}
