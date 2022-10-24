
/*
 * Mods
 *
 * #define SHARED
 * #define DSRC
 *
 */

#include <iostream>

#ifdef SHARED
#include <memory>

class SomeT
{
        std::shared_ptr<SomeT> m_ptr;

public:
        SomeT() : m_ptr(nullptr) {}

        static bool tying(std::shared_ptr<SomeT>& h1, std::shared_ptr<SomeT>& h2)
        {
                if (h1 == nullptr || h2 == nullptr)
                        return false;

                h1->m_ptr = h2;
                h2->m_ptr = h1;

                return true;
        }
};

int run_shared()
{
	std::shared_ptr<SomeT> ptr1 = std::make_shared<SomeT>();
	std::shared_ptr<SomeT> ptr2 = std::make_shared<SomeT>();

        SomeT::tying(ptr1, ptr2);

	//memleak
        return 0;
}
#endif


#ifdef DSRC
#include "dsrc_ptr.h"

class SomeT
{
        dsrc_ptr<SomeT> m_ptr;

public:
        SomeT() : m_ptr(nullptr) {}

        static bool tying(dsrc_ptr<SomeT>& h1, dsrc_ptr<SomeT>& h2)
        {
                if (h1 == nullptr || h2 == nullptr)
                        return false;

                h1->m_ptr = h2;
                h2->m_ptr = h1;

                return true;
        }
};

int run_dsrc()
{
        dsrc_ptr<SomeT> ptr1 = dsrc_ptr<SomeT>::make();
        dsrc_ptr<SomeT> ptr2 = dsrc_ptr<SomeT>::make();

        SomeT::tying(ptr1, ptr2);

        dsrc_ptr<SomeT>::free(ptr1);
        dsrc_ptr<SomeT>::free(ptr2);

        return 0;
}
#endif

#ifdef DSRC_DEBUG
#include <string>
#include "dsrc_ptr.h"

class SomeT
{
	std::string data;
        dsrc_ptr<SomeT> m_ptr;

public:
	SomeT(std::string& dt) : data(dt), m_ptr(nullptr) {}
	~SomeT() { std::cout << "destroyer of " << data << std::endl; }

        static bool tying(dsrc_ptr<SomeT>& h1, dsrc_ptr<SomeT>& h2)
        {
                if (h1 == nullptr || h2 == nullptr)
                        return false;

                h1->m_ptr = h2;
                h2->m_ptr = h1;

                return true;
        }
};

int run_dsrc_debug()
{
        dsrc_ptr<SomeT> ptr1 = dsrc_ptr<SomeT>::make(std::string("ptr1"));
        dsrc_ptr<SomeT> ptr2 = dsrc_ptr<SomeT>::make(std::string("ptr2"));

        SomeT::tying(ptr1, ptr2);

        dsrc_ptr<SomeT>::free(ptr1);
        dsrc_ptr<SomeT>::free(ptr2);

        return 0;
}
#endif

////////////////////////////////////////////

int main()
{
	try
	{
#ifdef SHARED
	run_shared();
#endif

#ifdef DSRC
		run_dsrc();
#endif

#ifdef DSRC_DEBUG
		run_dsrc_debug();
#endif

	}
	catch (std::string& message)
	{
		std::cout << "main catch exception type string, messige is \"" << message  << "\"" << std::endl;
	}
	catch(...)
	{
		std::cout << "main catch unknown type exception" << std::endl;
	}
}


