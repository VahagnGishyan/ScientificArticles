
#include "TestFunctions.hpp"

namespace TestFunctions
{
	namespace OneFunction
	{
		namespace Enum
		{
			static void ThrowException()
			{
				throw Enum::Error::SomeError;
			}

			void RunExcept()
			{
				try
				{
					ThrowException();
				}
				catch(const Enum::Error& error)
				{
					//handling
				}
			}
			
			//////////////////////////////////////////////////////////////////////////////////

			static void SetState(Error& state)
			{
				state = Enum::Error::SomeError;
			}

			void RunState()
			{
				Error state = Error::Unset;
				SetState(state);
				if (state == Error::SomeError)
				{
					//handling
				}
			}
		}
		namespace SameType
		{
			static void ThrowExcaption()
			{
				throw std::exception(std::string("Some message"));
			}

			void RunExcept()
			{
				try
				{
					ThrowExcaption();
				}
				catch (const std::exception& error)
				{
					//handling
				}
			}

			//////////////////////////////////////////////////////////////////////////////////

			struct StateObject
			{
			public:
				Error state = Error::Unset;
				std::unique_ptr<std::exception> data = nullptr;
			};

			static void SetState(StateObject& stateobj)
			{
				stateobj.state = Error::SomeError;
				stateobj.data = std::make_unique<std::exception>(std::string("Some message"));
			}

			void RunState()
			{
				StateObject stateobj;
				SetState(stateobj);
				if (stateobj.state == Error::SomeError)
				{
					stateobj.state = Error::Unset;
					stateobj.data;
					//handling
				}
			}
		}

		namespace SomeTypes
		{
			static void ThrowExcaption()
			{
				throw std::string("Some message");
			}

			void RunExcept()
			{
				try
				{
					ThrowExcaption();
				}
				catch (const std::exception& error)
				{
					//handling
				}
				catch (const std::string& error)
				{
					//handling
				}
			}

			//////////////////////////////////////////////////////////////////////////////////

			struct StateObject
			{
			public:
				Error state = Error::Unset;
				void* data = nullptr;
			};

			static void SetState(StateObject& stateobj)
			{
				stateobj.state = Error::Error2;
				stateobj.data = new std::string("Some message");
			}

			void RunState()
			{
				StateObject stateobj;
				SetState(stateobj);
				if (stateobj.state == Error::Error1)
				{
					std::exception* data = static_cast<std::exception*>(stateobj.data);
					//handling
					stateobj.state = Error::Unset;
					delete data;
				}
				else if (stateobj.state == Error::Error2)
				{
					std::string* data = static_cast<std::string*>(stateobj.data);
					//handling
					stateobj.state = Error::Unset;
					delete data;
				}
			}
		}
	}
}
