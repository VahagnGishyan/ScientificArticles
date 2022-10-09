#pragma once

#include <exception>
#include <string>
#include <memory>

namespace TestFunctions
{
	namespace OneFunction
	{
		namespace Enum
		{
			enum class Error
			{
				Unset,
				SomeError
			};

			void RunExcept();
			void RunState();
		}

		namespace SameType
		{
			// for examle std::exception
			
			enum class Error
			{
				Unset,
				SomeError
			};

			void RunExcept();
			void RunState();
		}

		namespace SomeTypes
		{
			// for examle std::exception

			enum class Error
			{
				Unset,
				Error1, // std::exception
				Error2, // std::string
			};

			void RunExcept();
			void RunState();
		}
	}
	namespace TenFunction
	{
		namespace Enum
		{
			enum class Error
			{
				Unset,
				SomeError
			};

			void RunExcept();
			void RunState();
		}

		namespace SameType
		{
			// for examle std::exception

			enum class Error
			{
				Unset,
				SomeError
			};

			void RunExcept();
			void RunState();
		}

		namespace SomeTypes
		{
			// for examle std::exception

			enum class Error
			{
				Unset,
				Error1, // std::exception
				Error2, // std::string
			};

			void RunExcept();
			void RunState();
		}
	}
	namespace IndexOfFunc
	{
		void RunExcept();
		void RunState();
	}
}

