
#include "TestFunctions.hpp"

namespace TestFunctions
{
	namespace IndexOfFunc
	{
		struct IncorrectInput {};
		struct NotFound {};

		int index_of(const char* const array, const char symbol)
		{
			if (array == nullptr)
			{
				throw IncorrectInput();
			}

			int index = 0;
			while (array[index] != '\0')
			{
				if (array[index] == symbol)
				{
					return (index);
				}
				++index;
			}
			throw NotFound();
		}

		void RunExcept()
		{
			const char* const array[] = { nullptr, "", "a", "abc", "qwertyuiopasdfghjklzxcvbnm" };
			char symbols[] = { 'a', '0', '=' };

			const int sarr = sizeof(array) / sizeof(array[0]);
			const int ssym = sizeof(symbols) / sizeof(symbols[0]);
			for (int iarr = 0; iarr < sarr; ++iarr)
			{
				for (int isym = 0; isym < ssym; ++isym)
				{
					try
					{
						index_of(array[iarr], symbols[isym]);
					}
					catch (const IncorrectInput& obj) { /*handling*/ }
					catch (const NotFound& obj) { /*handling*/ }
					catch (...) { throw "unknown error"; }
				}
			}
		}

		//////////////////////////////////////////////////////////////////////////////////

		enum class Error
		{
			Unset,
			IncorrectInput,
			NotFound,
		};

		int index_of(const char* const array, const char symbol, Error& state)
		{
			if (array == nullptr)
			{
				state = Error::IncorrectInput; return -1;
			}

			int index = 0;
			while (array[index] != '\0')
			{
				if (array[index] == symbol)
				{
					return (index);
				}
				++index;
			}
			state = Error::NotFound; return -1;
		}

		void RunState()
		{
			const char* const array[] = { nullptr, "", "a", "abc", "qwertyuiopasdfghjklzxcvbnm" };
			char symbols[] = { 'a', '0', '=' };

			const int sarr = sizeof(array) / sizeof(array[0]);
			const int ssym = sizeof(symbols) / sizeof(symbols[0]);
			for (int iarr = 0; iarr < sarr; ++iarr)
			{
				for (int isym = 0; isym < ssym; ++isym)
				{
					Error state = Error::Unset;
					index_of(array[iarr], symbols[isym], state);
					if (state == Error::IncorrectInput)
					{
						//handling
					}
					else if (state == Error::NotFound)
					{
						//handling
					}
				}
			}
		}
	}
}
