#ifndef MYRESUME_INTERPOLATOR_H
#define MYRESUME_INTERPOLATOR_H

class Interpolator
{
public:
	Interpolator(void);
	~Interpolator(void);

	virtual float calc(float);
};

#endif