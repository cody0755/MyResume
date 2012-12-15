#include "StdAfx.h"
#include "AlarmClockManager.h"
#include <algorithm>
#include "AlarmClock.h"

AlarmClockManager::AlarmClockManager(void)
{}

AlarmClockManager::~AlarmClockManager(void)
{}

void AlarmClockManager::push(AlarmClock *a)
{
	if (!a)
	{
		return;
	}
	alarms.push_back(a);
}

void AlarmClockManager::pop(AlarmClock *a)
{
	if (!a || alarms.empty())
	{
		return;
	}
	AlarmClockList::iterator iter = find(alarms.begin(), alarms.end(), a);
	if (iter != alarms.end())
	{
		alarms.erase(iter);
	}
}

AlarmClockManager& AlarmClockManager::instance()
{
	static AlarmClockManager inst;
	return inst;
}

void AlarmClockManager::tick(int tick_count)
{
	if (alarms.empty())
	{
		return;
	}
	vector<AlarmClock*> dead_alarms;
	AlarmClockList::iterator iter = alarms.begin();
	AlarmClockList::iterator iter_end = alarms.end();
	for (; iter != iter_end; ++iter)
	{
		if (*iter)
		{
			(*iter)->tick(tick_count);
			if (!(*iter)->running())
			{
				dead_alarms.push_back(*iter);
			}
		}
	}
	for (size_t i=0; i<dead_alarms.size(); ++i)
	{
		iter = find(alarms.begin(), alarms.end(), dead_alarms[i]);
		if (iter != alarms.end())
		{
			alarms.erase(iter);
		}
	}
}