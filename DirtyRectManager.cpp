#include "StdAfx.h"
#include "DirtyRectManager.h"

DirtyRectManager::DirtyRectManager(void)
{
	memset(&dirty_rect, 0, sizeof(dirty_rect));
}

DirtyRectManager::~DirtyRectManager(void)
{}

DirtyRectManager& DirtyRectManager::instance()
{
	static DirtyRectManager inst;
	return inst;
}

void DirtyRectManager::union_rect(const RECT& rhs)
{
	if (!valid_rect(rhs))
	{
		return;
	}
	if (!valid_rect(dirty_rect))
	{
		dirty_rect = rhs;
		return ;
	}
	dirty_rect.left = min(dirty_rect.left, rhs.left);
	dirty_rect.right = max(dirty_rect.right, rhs.right);
	dirty_rect.top = min(dirty_rect.top, rhs.top);
	dirty_rect.bottom = max(dirty_rect.bottom, rhs.bottom);
}

void DirtyRectManager::clear()
{
	memset(&dirty_rect, 0, sizeof(dirty_rect));
}

DirtyRectManager::operator RECT() const
{
	return dirty_rect;
}

DirtyRectManager::operator const RECT &() const
{
	return dirty_rect;
}

bool DirtyRectManager::is_intersecting(const RECT& rhs) const
{
	if (!valid_rect(dirty_rect)
		|| !valid_rect(rhs))
	{
		return false;
	}
	return (rhs.left <= dirty_rect.right
		&& dirty_rect.left <= rhs.right
		&& rhs.top <= dirty_rect.bottom
		&& dirty_rect.top <= rhs.bottom);
}

bool DirtyRectManager::valid_rect(const RECT& rhs) const
{
	return (rhs.bottom - rhs.top > 0
		&& rhs.right - rhs.left > 0);
}