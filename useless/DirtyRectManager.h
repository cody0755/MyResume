#ifndef USELESS_DIRTYRECTMANAGER_H
#define USELESS_DIRTYRECTMANAGER_H

#include "object.h"
class DirtyRectManager : public Object
{
public:
	static DirtyRectManager& instance();
	void union_rect(const Rect& rhs);
	void clear();
	const Rect& get_rect() const;
	bool is_intersecting(const Rect& rhs) const;
	bool is_none() const;

private:
	DirtyRectManager(void);
	~DirtyRectManager(void);

	Rect dirty_rect;
};

#endif

