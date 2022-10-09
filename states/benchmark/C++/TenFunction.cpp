
#include "TestFunctions.hpp"

namespace TestFunctions
{
	namespace TenFunction
	{
		namespace Enum
		{
			static void ThrowException()
			{
				throw Enum::Error::SomeError;
			}

			static void Func0() { ThrowException(); }
			static void Func1() { Func0(); }
			static void Func2() { Func1(); }
			static void Func3() { Func2(); }
			static void Func4() { Func3(); }
			static void Func5() { Func4(); }
			static void Func6() { Func5(); }
			static void Func7() { Func6(); }
			static void Func8() { Func7(); }
			static void Func9() { Func8(); }

			void RunExcept()
			{
				try
				{
					Func9();
				}
				catch (const Enum::Error& error)
				{
					//handling
				}
			}

			//////////////////////////////////////////////////////////////////////////////////

			static void SetState(Error& state)
			{
				state = Enum::Error::SomeError;
			}

			static void Func0(Error& state) { SetState(state); if (state != Enum::Error::Unset) { return; } }
			static void Func1(Error& state) { Func0(state); if (state != Enum::Error::Unset) { return; } }
			static void Func2(Error& state) { Func1(state); if (state != Enum::Error::Unset) { return; } }
			static void Func3(Error& state) { Func2(state); if (state != Enum::Error::Unset) { return; } }
			static void Func4(Error& state) { Func3(state); if (state != Enum::Error::Unset) { return; } }
			static void Func5(Error& state) { Func4(state); if (state != Enum::Error::Unset) { return; } }
			static void Func6(Error& state) { Func5(state); if (state != Enum::Error::Unset) { return; } }
			static void Func7(Error& state) { Func6(state); if (state != Enum::Error::Unset) { return; } }
			static void Func8(Error& state) { Func7(state); if (state != Enum::Error::Unset) { return; } }
			static void Func9(Error& state) { Func8(state); if (state != Enum::Error::Unset) { return; } }

			void RunState()
			{
				Error state = Error::Unset;
				Func9(state);
				if (state == Error::SomeError)
				{
					//handling
				}
			}
		}
		namespace SameType
		{
			static void ThrowException()
			{
				throw std::exception("Some message");
			}

			static void Func0() { ThrowException(); }
			static void Func1() { Func0(); }
			static void Func2() { Func1(); }
			static void Func3() { Func2(); }
			static void Func4() { Func3(); }
			static void Func5() { Func4(); }
			static void Func6() { Func5(); }
			static void Func7() { Func6(); }
			static void Func8() { Func7(); }
			static void Func9() { Func8(); }

			void RunExcept()
			{
				try
				{
					Func9();
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
				stateobj.data = std::make_unique<std::exception>("Some message");
			}

			static void Func0(StateObject& state) { SetState(state); if (state.state != Error::Unset) { return; } }
			static void Func1(StateObject& state) { Func0(state); if (state.state != Error::Unset) { return; } }
			static void Func2(StateObject& state) { Func1(state); if (state.state != Error::Unset) { return; } }
			static void Func3(StateObject& state) { Func2(state); if (state.state != Error::Unset) { return; } }
			static void Func4(StateObject& state) { Func3(state); if (state.state != Error::Unset) { return; } }
			static void Func5(StateObject& state) { Func4(state); if (state.state != Error::Unset) { return; } }
			static void Func6(StateObject& state) { Func5(state); if (state.state != Error::Unset) { return; } }
			static void Func7(StateObject& state) { Func6(state); if (state.state != Error::Unset) { return; } }
			static void Func8(StateObject& state) { Func7(state); if (state.state != Error::Unset) { return; } }
			static void Func9(StateObject& state) { Func8(state); if (state.state != Error::Unset) { return; } }

			void RunState()
			{
				StateObject stateobj;
				Func9(stateobj);
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
			static void ThrowException()
			{
				throw std::string("Some message");
			}

			static void Func0() { ThrowException(); }
			static void Func1() { Func0(); }
			static void Func2() { Func1(); }
			static void Func3() { Func2(); }
			static void Func4() { Func3(); }
			static void Func5() { Func4(); }
			static void Func6() { Func5(); }
			static void Func7() { Func6(); }
			static void Func8() { Func7(); }
			static void Func9() { Func8(); }

			void RunExcept()
			{
				try
				{
					Func9();
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

			static void Func0(StateObject& state) { SetState(state); if (state.state != Error::Unset) { return; } }
			static void Func1(StateObject& state) { Func0(state); if (state.state != Error::Unset) { return; } }
			static void Func2(StateObject& state) { Func1(state); if (state.state != Error::Unset) { return; } }
			static void Func3(StateObject& state) { Func2(state); if (state.state != Error::Unset) { return; } }
			static void Func4(StateObject& state) { Func3(state); if (state.state != Error::Unset) { return; } }
			static void Func5(StateObject& state) { Func4(state); if (state.state != Error::Unset) { return; } }
			static void Func6(StateObject& state) { Func5(state); if (state.state != Error::Unset) { return; } }
			static void Func7(StateObject& state) { Func6(state); if (state.state != Error::Unset) { return; } }
			static void Func8(StateObject& state) { Func7(state); if (state.state != Error::Unset) { return; } }
			static void Func9(StateObject& state) { Func8(state); if (state.state != Error::Unset) { return; } }

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
