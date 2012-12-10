#ifndef MYRESUME_ACTIVITYMANAGER_H
#define MYRESUME_ACTIVITYMANAGER_H

#include "object.h"
#include <list>

class Activity;
typedef list<Activity*> ActivityContainer;
class ActivityManager : public Object
{
private:
	ActivityManager(void);
	virtual ~ActivityManager(void);
public:
	static ActivityManager& instance();
	void push(Activity *rhs);
	void pop();
	Activity* top() const;
	bool empty() const;

private:
	ActivityContainer activities;
};

#endif