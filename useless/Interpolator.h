#ifndef USELESS_INTERPOLATOR_H
#define USELESS_INTERPOLATOR_H

#include "noncopyable.h"

class Interpolator : private noncopyable
{
public:
	virtual float calc(float) = 0;
};

class LinearInterpolator : public Interpolator
{
public:
	virtual float calc(float);
};

class AccelerateInterpolator : public Interpolator
{
public:
	virtual float calc(float);
};

class DecelerateInterpolator : public Interpolator
{
public:
	virtual float calc(float);
};

class CycleInterpolator : public Interpolator
{
public:
	virtual float calc(float);
};

class AccelerateDecelerateInterpolator : public Interpolator
{
public:
	virtual float calc(float);
};

#endif