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
		(*iter)->on_destroy();
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
	pop();

	activities.push_back(rhs);

	rhs->on_create();
}

void ActivityManager::pop()
{
	if (activities.empty())
	{
		return;
	}
	Activity *a = activities.back();
	activities.pop_back();

	a->on_destroy();
	delete a;
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
