#include "StdAfx.h"
#include "ActivityManager.h"
#include "Activity.h"

ActivityManager::ActivityManager(void)
{
}

ActivityManager::~ActivityManager(void)
{
	ActivityContainer::iterator iter = activities.begin();
	for (; iter != activities.end(); ++iter)
	{
		delete *iter;
	}
}

ActivityManager& ActivityManager::instance()
{
	static ActivityManager inst;
	return inst;
}

void ActivityManager::push(Activity *rhs)
{
	if (!rhs)
	{
		return;
	}
	activities.push_back(rhs);
}

void ActivityManager::pop()
{
	if (activities.empty())
	{
		return;
	}
	Activity *a = activities.back();
	delete a;
	activities.pop_back();
}

Activity* ActivityManager::top() const
{
	if (activities.empty())
	{
		return NULL;
	}
	return activities.back();
}

bool ActivityManager::empty() const
{
	return activities.empty();
}
