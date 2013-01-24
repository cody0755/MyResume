#ifndef USELESS_NONCOPYABLE_H
#define USELESS_NONCOPYABLE_H

class noncopyable
{
protected:
	noncopyable(){}
	~noncopyable(){};
private:
	noncopyable(const noncopyable&);
	noncopyable& operator=(const noncopyable&);
};

#endif