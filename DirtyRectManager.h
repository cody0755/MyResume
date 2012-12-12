#ifndef MYRESUME_DIRTYRECTMANAGER_H
#define MYRESUME_DIRTYRECTMANAGER_H

#include "object.h"
class DirtyRectManager : public Object
{
public:
	static DirtyRectManager& instance();
	void union_rect(const RECT& rhs);
	void clear();
	const RECT& get_rect() const;
	bool is_intersecting(const RECT& rhs) const;
	bool is_none() const;

private:
	DirtyRectManager(void);
	~DirtyRectManager(void);
	bool valid_rect(const RECT& rhs) const;

	RECT dirty_rect;
};

#endif

