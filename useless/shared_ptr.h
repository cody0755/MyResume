#ifndef USELESS_SHARED_PTR_H
#define USELESS_SHARED_PTR_H

template <class T>
class shared_ptr
{
public:
	shared_ptr(const T *o = NULL)
	: obj(o)
	{
		count = new size_t;
		if (obj)
		{
			*count = 1;
		} 
		else
		{
			*count = 0;
		}
	}

	template <class Y>
	shared_ptr(const Y *o)
	: obj(o)
	{
		count = new size_t;
		*count = 1;
	}

	~shared_ptr()
	{
		release();
	}

	shared_ptr(const shared_ptr &rhs)
	: obj(rhs.obj)
	, count(rhs.count)
	{
		if (obj)
		{
			++*count;
		}
	}

	shared_ptr& operator=(const shared_ptr &rhs)
	{
		if (this == &rhs || obj == rhs.obj)
		{
			return *this;
		}
		
		release();
		obj = rhs.obj;
		count = rhs.count;
		++*count;
	}

	T* operator->() const
	{
		return obj;
	}

	T& operator*() const
	{
		return *obj;
	}

	bool valid() const {return obj != NULL;}

private:
	void release()
	{
		if (count)
		{
			--*count;
			if (*count == 0)
			{
				delete obj;
				delete count;
			}
		}
	}

	T *obj;
	size_t *count;
};

#endif