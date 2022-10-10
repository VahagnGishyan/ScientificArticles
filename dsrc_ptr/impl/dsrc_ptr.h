
#pragma once

#include <assert.h>
#ifndef RELEASE
#include "errlog.h"
#else 
#include <iostream>
#include <string>
#endif

template<typename valueT>
class dsrc_ptr
{
private:
	using uint = unsigned int;
public:

	dsrc_ptr(nullptr_t) :
		m_data(nullptr)
#ifndef RELEASE
		, m_ref_count (new uint(0))
		, m_is_deleted(new bool(true))
#endif
	{}

private:
	template <class... ArgsT>
	explicit dsrc_ptr(ArgsT&&... args) :
		m_data(new valueT(args...))
#ifndef RELEASE
		, m_ref_count(new uint(1))
		, m_is_deleted(new bool(false))
#endif
	{}

	///////////////////////////////////////////////////////////////////////////

public:
	dsrc_ptr(const dsrc_ptr& obj)
	{
		m_data = obj.m_data;
#ifndef RELEASE
		if (obj.m_data == nullptr)
		{
			return;
		}
		m_ref_count = obj.m_ref_count;
		m_is_deleted = obj.m_is_deleted;
		(*this->m_ref_count)++; // if the pointer is not null, increment the m_ref_count
#endif
	}

	dsrc_ptr(dsrc_ptr&& obj) noexcept
	{
		if (obj.m_data == nullptr)
		{
			m_data = nullptr;
			m_ref_count = nullptr;
			m_is_deleted = nullptr;
			return;
		}

		m_data = obj.m_data;
		obj.m_data = nullptr;
#ifndef RELEASE
		m_ref_count = obj.m_ref_count;
		m_is_deleted = obj.m_is_deleted;
		obj.m_ref_count = nullptr;
		obj.m_is_deleted = nullptr;
#endif
	}

	////////////////////////////////////////////////////////////////

	~dsrc_ptr()
	{
#ifndef RELEASE
		if (m_is_deleted == nullptr)
		{
			assert(m_data == nullptr && m_ref_count == nullptr);
			return;
		}

		if (*m_ref_count > 1)
		{
			--(*m_ref_count);
			return;
		}

		bool is_deleted = (*m_is_deleted == true);
		delete m_ref_count;
		delete m_is_deleted;

		if (is_deleted == true)
		{
			return;
		}

		delete m_data;
		std::cout << "dsrc_ptr destroyer, memory is not deallocated, call std::terminate" << std::endl;
		std::terminate();
#endif
	}

	///////////////////////////////////////////////////////////////////////////

	dsrc_ptr& operator=(const dsrc_ptr& obj) // copy assignment
	{
#ifndef RELEASE
		if (m_data != nullptr)
		{
			free(*this);
			throw std::string("dsrc_ptr::operator=(&&) throw exception, trying double alocate");
		}
#endif
		--(*m_ref_count);

		m_data = obj.m_data;
#ifndef RELEASE
		m_ref_count = obj.m_ref_count;
		m_is_deleted = obj.m_is_deleted;
		if (obj.m_data != nullptr)
		{
			--(*m_ref_count);
		}
#endif
		return (*this);
	}

	dsrc_ptr& operator=(dsrc_ptr&& obj) noexcept
	{
#ifndef RELEASE
		if (*m_ref_count > 1)
		{
			--(*m_ref_count);
		}
		else if (m_data != nullptr)
		{
			free(*this);
			errlog::writeln("dsrc_ptr::operator=(&&) throw exception, trying double alocate");
			std::terminate();
		}
		std::swap(m_ref_count, obj.m_ref_count);
		std::swap(m_is_deleted, obj.m_is_deleted);
#endif
		std::swap(m_data, obj.m_data);
		return (*this);
	}

	///////////////////////////////////////////////////////////////////////////

public:
	bool operator==(nullptr_t)
	{
		return (m_data == nullptr);
	}

	bool operator!=(nullptr_t)
	{
		return (!(m_data == nullptr));
	}

	/////////////////////////////////////////////////////////

	valueT& operator*()
	{
#ifndef RELEASE
		if (m_data == nullptr || (m_is_deleted != nullptr && *m_is_deleted == true))
		{
			throw std::string("dsrc_ptr::operator* throw exception, trying indirect nullptr");
		}
#endif
		return (*m_data);
	}

	valueT* operator->() const
	{
#ifndef RELEASE
		if (m_data == nullptr || (m_is_deleted != nullptr && *m_is_deleted == true))
		{
			throw std::string("dsrc_ptr::operator-> throw exception, trying access nullptr");
		}
#endif
		return m_data;
	}

	/////////////////////////////////////////////////////////

public:

	uint get_count() const
	{
#ifndef RELEASE
		if (m_data == nullptr || (m_is_deleted != nullptr && *m_is_deleted == true))
		{
			throw std::string("dsrc_ptr::operator-> throw exception, trying access nullptr");
		}
#endif
		return *m_ref_count;
	}

	/////////////////////////////////////////////////////////

public:
	template <class... ArgsT>
	static dsrc_ptr make(ArgsT&&... args)
	{
		return (dsrc_ptr(args...));
	}

	static void free(dsrc_ptr& ptr)
	{
#ifndef RELEASE
		if (ptr.m_is_deleted == nullptr)
		{
			assert(ptr.m_ref_count == nullptr && ptr.m_data == nullptr);
			return;
		}

		if (*ptr.m_is_deleted == true)
		{
			if (ptr.m_data != nullptr)
			{
				delete ptr.m_is_deleted;
				delete ptr.m_ref_count;
				ptr.m_ref_count = nullptr;
				ptr.m_is_deleted = nullptr;
				throw std::string("Trying deallocate already deallocated memory from ather ptr");
			}
			else
			{
				if (*ptr.m_ref_count == 0 || *ptr.m_ref_count == 1)
				{
					return;
				}
			}
		}

		*ptr.m_is_deleted = true;
#endif
		delete ptr.m_data;
		ptr.m_data = nullptr;
	}

	/////////////////////////////////////////////////////////

private:
	valueT* m_data;
	uint* m_ref_count = nullptr;
	bool* m_is_deleted = nullptr;
};
