#ifndef MYRESUME_INTERPOLATOR_H
#define MYRESUME_INTERPOLATOR_H

class Interpolator
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