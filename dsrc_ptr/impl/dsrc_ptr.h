#pragma once

//temp
#define DEBUG
//#define RELEASE

#include <assert.h>
#ifndef RELEASE
#include "errlog.h"
#else 
#include <iostream>
#include <string>
#endif

namespace dsrc
{
	template<typename valueT>
	class unique_ptr
	{
	public:
		unique_ptr(nullptr_t) : m_data(nullptr) {}

		unique_ptr(unique_ptr&& robj) noexcept : unique_ptr(nullptr)
		{
#ifndef RELEASE
			if (m_data != nullptr)
			{
				free(*this);
				errlog::writeln("dsrc_ptr(&&) throw exception, trying double alocate");
				std::terminate();
			}
#endif
			m_data = robj.m_data;
			robj.m_data = nullptr;
		}

		~unique_ptr()
		{
#ifndef RELEASE
			if (m_data == nullptr)
			{
				return;
			}
			free(*this);
			std::cout << "dsrc_ptr destroyer throw exception, memory is not deallocated" << std::endl;
			std::terminate();
#endif
		}

	private:

		template <class... ArgsT>
		explicit unique_ptr(ArgsT&&... args)
		{
			m_data = new valueT(args...);
		}

		explicit unique_ptr(unique_ptr& lobj) : m_data(lobj.m_data)
		{
			lobj.m_data = nullptr;
		}

		/////////////////////////////////////////////////////////

	public:

		//
		//unique_ptr& operator=(const unique_ptr& robj)
		//{
		//	if (m_data != nullptr)
		//	{
		//		free(*this);
		//		throw std::string("dsrc_ptr::operator=(&&) throw exception, trying double alocate");
		//	}
		//
		//	m_data = robj.m_data;
		//	robj.m_data = nullptr;
		//	return (*this);
		//}

		unique_ptr& operator=(unique_ptr&& robj)
		{
#ifndef RELEASE
			if (m_data != nullptr)
			{
				free(*this);
				throw std::string("dsrc_ptr::operator=(&&) throw exception, trying double alocate");
			}
#endif

			m_data = robj.m_data;
			robj.m_data = nullptr;
			return (*this);
		}

		/////////////////////////////////////////////////////////

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
			if (m_data == nullptr)
			{
				throw std::string("dsrc_ptr::operator* throw exception, trying indirect nullptr");
			}
#endif
			return (*m_data);
		}

		valueT* operator->()
		{
#ifndef RELEASE
			if (m_data == nullptr)
			{
				throw std::string("dsrc_ptr::operator-> throw exception, trying access nullptr");
			}
#endif
			return m_data;
		}

		/////////////////////////////////////////////////////////
	public:
		template <class... ArgsT>
		static unique_ptr make(ArgsT&&... args)
		{
			unique_ptr ptr(args...);
			return (ptr);
		}

		static void free(unique_ptr& ptr)
		{
			delete ptr.m_data;
			ptr.m_data = nullptr;
		}

		/////////////////////////////////////////////////////////

	private:
		valueT* m_data;
	};
}
