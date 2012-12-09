#ifndef MYRESUME_DIRTYRECTMANAGER_H
#define MYRESUME_DIRTYRECTMANAGER_H

#include "object.h"
class DirtyRectManager : public Object
{
public:
	static DirtyRectManager& instance();
	void union_rect(const RECT& rhs);
	void clear();
	operator RECT() const;
	operator const RECT&() const;
	bool is_intersecting(const RECT& rhs) const;

private:
	DirtyRectManager(void);
	~DirtyRectManager(void);
	bool valid_rect(const RECT& rhs) const;

	RECT dirty_rect;
};

#endif

