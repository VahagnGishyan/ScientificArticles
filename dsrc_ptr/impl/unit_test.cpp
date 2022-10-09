
#include <list>
#include <functional>
#include "dsrc_ptr.h"

namespace dsrc
{
	namespace unit_test
	{
		template <typename valueT>
		static void success_test_00()
		{
			dsrc::unique_ptr<valueT> ptr = nullptr;
		}

		/////////////////////////////////////////////////////////

		template <typename valueT>
		static void success_test_01()
		{
			dsrc::unique_ptr<valueT> ptr = nullptr;
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		/////////////////////////////////////////////////////////

		template <typename valueT, class... ArgsT>
		static void success_test_02(ArgsT&&... args)
		{
			dsrc::unique_ptr<valueT> ptr = nullptr;
			ptr = std::move(dsrc::unique_ptr<valueT>::make(args...));
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		/////////////////////////////////////////////////////////

		template <typename valueT, class... ArgsT>
		static void success_test_03(ArgsT&&... args)
		{
			dsrc::unique_ptr<valueT> ptr = nullptr;
			ptr = std::move(dsrc::unique_ptr<valueT>::make(args...));
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		/////////////////////////////////////////////////////////

		template <typename valueT, class... ArgsT>
		static void success_test_04(ArgsT&&... args)
		{
			dsrc::unique_ptr<valueT> ptr = nullptr;
			ptr = std::move(dsrc::unique_ptr<valueT>::make(args...));
			*ptr;
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		/////////////////////////////////////////////////////////

		template <typename valueT, class... ArgsT>
		static void success_test_05(ArgsT&&... args)
		{
			dsrc::unique_ptr<valueT> ptr1 = nullptr;
			dsrc::unique_ptr<valueT> ptr2 = nullptr;
		
			ptr1 = std::move(dsrc::unique_ptr<valueT>::make(args...));
			assert(ptr1 != nullptr);
			ptr2 = std::move(ptr1);
			dsrc::unique_ptr<valueT>::free(ptr2);
		}

		/////////////////////////////////////////////////////////

		template <typename valueT>
		static void success_test_06_func(dsrc::unique_ptr<valueT>& ptr)
		{
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		template <typename valueT, class... ArgsT>
		static void success_test_06(ArgsT&& ... args)
		{
			dsrc::unique_ptr<valueT> ptr = nullptr;
			ptr = std::move(dsrc::unique_ptr<valueT>::make(args...));
			success_test_06_func(ptr);
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		/////////////////////////////////////////////////////////

		template <typename valueT>
		static void success_test_07_func(dsrc::unique_ptr<valueT> ptr)
		{
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		template <typename valueT, class... ArgsT>
		static void success_test_07(ArgsT&&... args)
		{
			dsrc::unique_ptr<valueT> ptr = nullptr;
			ptr = std::move(dsrc::unique_ptr<valueT>::make(args...));
			success_test_07_func(std::move(ptr));
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		///////////////////////////////////////////////////////

		template <typename valueT, class... ArgsT>
		static void success_test_08(ArgsT&&... args)
		{
			dsrc::unique_ptr<valueT> ptr = dsrc::unique_ptr<valueT>::make(args...);
			dsrc::unique_ptr<valueT>::free(ptr);
		}

		/////////////////////////////////////////////////////////

		template <typename valueT, class... ArgsT>
		static void success_run(ArgsT&&... args)
		{
			success_test_00<valueT>();
			success_test_01<valueT>();
			success_test_02<valueT>(args...);
			success_test_03<valueT>(args...);
			success_test_04<valueT>(args...);
			success_test_05<valueT>(args...);
			success_test_06<valueT>(args...);
			success_test_07<valueT>(args...);
			success_test_08<valueT>(args...);
		}

		void success_run()
		{
			success_run<int>(4);
			success_run<double>(12.78);
			
			struct SomeT 
			{
				SomeT(int aiv1, int aiv2, double adv) : iv1(aiv1), iv2(aiv2), dv(adv) {}

				int iv1; 
				int iv2; 
				double dv; 
			};
			success_run<SomeT>(48, 478, 123.456);
		}

		/////////////////////////////////////////////////////////
		//
		/////////////////////////////////////////////////////////
		
		template <typename valueT>
		static void fail_test_00()
		{
#ifndef RELEASE
			try
			{
				dsrc::unique_ptr<valueT> ptr = nullptr;
				valueT value = *ptr;
			}
			catch (...)
			{
				return;
			}
			throw std::string("function fail_test_00");
#endif
		}

		template <typename valueT, class... ArgsT>
		static void fail_test_01(ArgsT&&... args)
		{
#ifndef RELEASE
			try
			{
				dsrc::unique_ptr<valueT> ptr = nullptr;
				ptr = dsrc::unique_ptr<valueT>::make(args...);
				dsrc::unique_ptr<valueT>::free(ptr);
				valueT value = *ptr;
			}
			catch (...)
			{
				return;
			}
			throw std::string("function fail_test_01");
#endif
		}
		
		template <typename valueT, class... ArgsT>
		static void fail_test_02(ArgsT&&... args)
		{
#ifndef RELEASE
			try
			{
				dsrc::unique_ptr<valueT> ptr = dsrc::unique_ptr<valueT>::make(args...);
				dsrc::unique_ptr<valueT>::free(ptr);
				valueT value = *ptr;
			}
			catch (...)
			{
				return;
			}
			throw std::string("function fail_test_02");
#endif
		}

		template <typename valueT, class... ArgsT>
		static void fail_test_03(ArgsT&&... args)
		{
#ifndef RELEASE
			//try
			//{
			//	dsrc::unique_ptr<valueT> ptr = nullptr;
			//	ptr = dsrc::unique_ptr<valueT>::make(args...);
			//}
			//catch (...)
			//{
			//	return;
			//}
			//throw std::string("function fail_test_03");
#endif
		}

		template <typename valueT, class... ArgsT>
		static void fail_test_04(ArgsT&&... args)
		{
#ifndef RELEASE

			//try
			//{
			//	dsrc::unique_ptr<valueT> ptr = dsrc::unique_ptr<valueT>::make(args...);
			//}
			//catch (...)
			//{
			//	return;
			//}
			//throw std::string("function fail_test_04");
#endif
		}
		
		template <typename valueT, class... ArgsT>
		static void fail_run(ArgsT... args)
		{
#ifndef RELEASE
			fail_test_00<valueT>();
			fail_test_01<valueT>(args...);
			fail_test_02<valueT>(args...);
			fail_test_03<valueT>(args...);
			fail_test_04<valueT>(args...);
#endif
		}

		void fail_run()
		{
#ifndef RELEASE
			fail_run<int>(1478);
			fail_run<double>(454.848748);

			struct SomeT { int iv1; int iv2; double dv; };
			fail_run<SomeT>();
#endif
		}
	}
}
