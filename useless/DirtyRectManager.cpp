#include "DirtyRectManager.h"

DirtyRectManager::DirtyRectManager(void)
{}

DirtyRectManager::~DirtyRectManager(void)
{}

DirtyRectManager& DirtyRectManager::instance()
{
	static DirtyRectManager inst;
	return inst;
}

void DirtyRectManager::union_rect(const Rect& rhs)
{
	dirty_rect.union_rect(rhs);
}

void DirtyRectManager::clear()
{
	dirty_rect.clear();
}

const Rect& DirtyRectManager::get_rect() const
{
	return dirty_rect;
}

bool DirtyRectManager::is_intersecting(const Rect& rhs) const
{
	return dirty_rect.is_intersecting(rhs);
}

bool DirtyRectManager::is_none() const
{
	return !dirty_rect.valid();
}