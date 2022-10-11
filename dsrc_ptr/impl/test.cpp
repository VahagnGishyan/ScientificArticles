
#include "test.h"

namespace test
{
	template <typename valueT>
	static void success_test_00()
	{
		dsrc_ptr<valueT> ptr = nullptr;
	}

	/////////////////////////////////////////////////////////

	template <typename valueT>
	static void success_test_01()
	{
		dsrc_ptr<valueT> ptr = nullptr;
		dsrc_ptr<valueT>::free(ptr);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_02(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr = nullptr;
		ptr = std::move(dsrc_ptr<valueT>::make(args...));
		dsrc_ptr<valueT>::free(ptr);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_03(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr = nullptr;
		ptr = std::move(dsrc_ptr<valueT>::make(args...));
		dsrc_ptr<valueT>::free(ptr);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_04(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr = nullptr;
		ptr = std::move(dsrc_ptr<valueT>::make(args...));
		*ptr;
		dsrc_ptr<valueT>::free(ptr);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_05(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = nullptr;
		dsrc_ptr<valueT> ptr2 = nullptr;

		ptr1 = std::move(dsrc_ptr<valueT>::make(args...));
		assert(ptr1 != nullptr);
		ptr2 = std::move(ptr1);
		dsrc_ptr<valueT>::free(ptr2);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT>
	static void success_test_06_func(dsrc_ptr<valueT>& ptr)
	{
		dsrc_ptr<valueT>::free(ptr);
	}

	template <typename valueT, class... ArgsT>
	static void success_test_06(ArgsT&& ... args)
	{
		dsrc_ptr<valueT> ptr = nullptr;
		ptr = std::move(dsrc_ptr<valueT>::make(args...));
		success_test_06_func(ptr);
		dsrc_ptr<valueT>::free(ptr);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT>
	static void success_test_07_func(dsrc_ptr<valueT> ptr)
	{
		dsrc_ptr<valueT>::free(ptr);
	}

	template <typename valueT, class... ArgsT>
	static void success_test_07(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr = nullptr;
		ptr = std::move(dsrc_ptr<valueT>::make(args...));
		success_test_07_func(std::move(ptr));
		dsrc_ptr<valueT>::free(ptr);
	}

	///////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_08(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr = dsrc_ptr<valueT>::make(args...);
		dsrc_ptr<valueT>::free(ptr);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_09(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = dsrc_ptr<valueT>::make(args...);
		dsrc_ptr<valueT> ptr2 = ptr1;
		dsrc_ptr<valueT> ptr3 = ptr1;
		dsrc_ptr<valueT>::free(ptr1);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_10(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = dsrc_ptr<valueT>::make(args...);
		dsrc_ptr<valueT>::free(ptr1);
		dsrc_ptr<valueT> ptr2 = ptr1;
		dsrc_ptr<valueT> ptr3 = ptr1;
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_11(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = dsrc_ptr<valueT>::make(args...);
		dsrc_ptr<valueT> ptr2 = ptr1;
		dsrc_ptr<valueT> ptr3 = ptr1;

		dsrc_ptr<valueT>::free(ptr3);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_12(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = dsrc_ptr<valueT>::make(args...);
		dsrc_ptr<valueT> ptr2 = std::move(ptr1);

		dsrc_ptr<valueT>::free(ptr2);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_13(ArgsT&&... args)
	{
		struct SomeT
		{
			SomeT(ArgsT&&... args) : ptr(dsrc_ptr<valueT>::make(args...)) {}
			~SomeT() { dsrc_ptr<valueT>::free(ptr); }

			dsrc_ptr<valueT>  data_obj() { return (ptr); }
			dsrc_ptr<valueT>& data_ref() { return (ptr); }

		private:
			dsrc_ptr<valueT> ptr;
		};

		SomeT obj(args...);

		dsrc_ptr<valueT> ptr1 = obj.data_obj();
		dsrc_ptr<valueT> ptr2 = obj.data_ref();

		dsrc_ptr<valueT> ptr3 = SomeT(args...).data_obj();
		dsrc_ptr<valueT> ptr4 = SomeT(args...).data_ref();
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_14(ArgsT&&... args)
	{
		class SomeT
		{
			dsrc_ptr<SomeT> m_ptr;

		public:

			SomeT() : m_ptr(nullptr) {}
			~SomeT() {}

			static bool tying(dsrc_ptr<SomeT>& h1, dsrc_ptr<SomeT>& h2)
			{
				if (h1 != nullptr || h2 != nullptr)
					return false;

				h1->m_ptr = h2;
				h2->m_ptr = h1;

				return true;
			}
		};

		auto ptr1 = dsrc_ptr<SomeT>::make();
		auto ptr2 = dsrc_ptr<SomeT>::make();

		SomeT::tying(ptr1, ptr2);
		//memleak

		dsrc_ptr<SomeT>::free(ptr1);
		dsrc_ptr<SomeT>::free(ptr2);
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_15(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = dsrc_ptr<valueT>::make(args...);
		dsrc_ptr<valueT> ptr2 = nullptr;

		dsrc_ptr<valueT>::free(ptr1);
		ptr1 = ptr2;
	}

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_16(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = dsrc_ptr<valueT>::make(args...);
		dsrc_ptr<valueT> ptr2 = dsrc_ptr<valueT>::make(args...);

		dsrc_ptr<valueT>::free(ptr1);
		ptr1 = ptr2;
		dsrc_ptr<valueT>::free(ptr1);
	}

	/////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////

	template <typename valueT, class... ArgsT>
	static void success_test_17(ArgsT&&... args)
	{
		dsrc_ptr<valueT> ptr1 = nullptr;
		dsrc_ptr<valueT> ptr2 = nullptr;

		ptr1 = ptr2;
		ptr1 = ptr2;

		ptr2 = ptr1;
		ptr2 = ptr1;
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
		success_test_09<valueT>(args...);
		success_test_10<valueT>(args...);
		success_test_11<valueT>(args...);
		success_test_12<valueT>(args...);
		success_test_13<valueT>(args...);
		success_test_14<valueT>(args...);
		success_test_15<valueT>(args...);
		success_test_16<valueT>(args...);
		success_test_17<valueT>(args...);
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
#ifdef DEBUG
		try
		{
			dsrc_ptr<valueT> ptr = nullptr;
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
#ifdef DEBUG
		try
		{
			dsrc_ptr<valueT> ptr = nullptr;
			ptr = dsrc_ptr<valueT>::make(args...);
			dsrc_ptr<valueT>::free(ptr);
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
#ifdef DEBUG
		try
		{
			dsrc_ptr<valueT> ptr = dsrc_ptr<valueT>::make(args...);
			dsrc_ptr<valueT>::free(ptr);
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
#ifdef DEBUG
		//destructor

		//try
		//{
		//	dsrc_ptr<valueT> ptr = nullptr;
		//	ptr = dsrc_ptr<valueT>::make(args...);
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
#ifdef DEBUG
		//destructor

		//try
		//{
		//	dsrc_ptr<valueT> ptr = dsrc_ptr<valueT>::make(args...);
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
#ifdef DEBUG
		fail_test_00<valueT>();
		fail_test_01<valueT>(args...);
		fail_test_02<valueT>(args...);
		fail_test_03<valueT>(args...);
		fail_test_04<valueT>(args...);
#endif
	}

	void fail_run()
	{
#ifdef DEBUG
		fail_run<int>(1478);
		fail_run<double>(454.848748);

		//struct SomeT { int iv1; int iv2; double dv; };
		//fail_run<SomeT>();
#endif
	}
}
