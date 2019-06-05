#pragma once
#include <type_traits>
#include <cocos/base/CCRef.h>


// PtrCocos2d

template<typename ClassType>
class PtrCocos2d
{
public:
	PtrCocos2d() noexcept
		: m_ptrClass(nullptr)
	{
		static_assert(std::is_base_of<cocos2d::Ref, ClassType>::value, "Should be child of cocos2d::Ref");
	}

	template<typename ... Args>
	static PtrCocos2d<ClassType> create(Args&& ... args)
	{
		static_assert(std::is_base_of<cocos2d::Ref, ClassType>::value, "Should be child of cocos2d::Ref");
		// retain внутри create
		return ClassType::create(std::forward<Args>(args)...);
	}

	PtrCocos2d(ClassType* ptr) noexcept
		: m_ptrClass(ptr)
	{
		if (m_ptrClass)
		{
			m_ptrClass->retain();
		}
	}

	PtrCocos2d(PtrCocos2d const& rhs, const bool addRef = false)
		: m_ptrClass(rhs.m_ptrClass)
	{
		if (m_ptrClass && addRef)
		{
			m_ptrClass->retain();
		}
	}

	template<class U>
	PtrCocos2d(PtrCocos2d<U> const& rhs)
		: m_ptrClass(rhs.get())
	{
		if (m_ptrClass)
		{
			m_ptrClass->retain();
		}
	}

	~PtrCocos2d()
	{
		if (m_ptrClass)
		{
			m_ptrClass->release();
		}
	}

	PtrCocos2d(PtrCocos2d&& rhs) noexcept
		: m_ptrClass(rhs.m_ptrClass)
	{
		// R-value; remove old ptr
		rhs.m_ptrClass = nullptr;
	}

	PtrCocos2d& operator=(PtrCocos2d&& rhs) noexcept
	{
		IntrusivePtrCocos2d(static_cast<PtrCocos2d&&>(rhs)).swap(*this);
		return *this;
	}

	PtrCocos2d& operator=(PtrCocos2d const& rhs)
	{
		PtrCocos2d(rhs).swap(*this);
		return *this;
	}

	PtrCocos2d& operator=(ClassType* rhs)
	{
		PtrCocos2d(rhs).swap(*this);
		return *this;
	}

	void reset() noexcept
	{
		PtrCocos2d().swap(*this);
	}

	void reset(ClassType* rhs)
	{
		PtrCocos2d(rhs).swap( *this );
	}

	void reset(ClassType* rhs, const bool addRef)
	{
		PtrCocos2d(rhs, addRef).swap(*this);
	}

	ClassType* get() const noexcept
	{
		return m_ptrClass;
	}

	ClassType& operator*() const
	{
		assert(m_ptrClass && !!"BAD PTR m_ptrClass!");
		return *m_ptrClass;
	}

	ClassType* operator->() const
	{
		assert(m_ptrClass && !!"BAD PTR m_ptrClass!");
		return m_ptrClass;
	}

	operator bool () const noexcept
	{
		return (nullptr != m_ptrClass);
	}

	inline bool operator==(PtrCocos2d<ClassType> const& b) const
	{
		return (b.get() == m_ptrClass);
	}

	inline bool operator!=(PtrCocos2d<ClassType> const& b) const
	{
		return (false == (b == *this));
	}

private:
	void swap(PtrCocos2d& rhs) noexcept
	{
		// TODO: проверить
		std::swap(m_ptrClass, rhs.m_ptrClass);
	}

	ClassType* m_ptrClass = nullptr;
};
