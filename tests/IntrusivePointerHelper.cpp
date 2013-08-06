#define BOOST_TEST_MODULE IntrusivePointerHelper
#include <boost/test/unit_test.hpp>

#include <yandex/contest/IntrusivePointeeBase.hpp>
#include <yandex/contest/detail/IntrusivePointerHelper.hpp>
#include <yandex/contest/detail/ForwardHeader.hpp>

BOOST_AUTO_TEST_SUITE(IntrusivePointerHelper)

YANDEX_CONTEST_INTRUSIVE_PTR_FWD_DECLARE(Test);

TestPointer createTest();
void checkTestCount(const std::size_t count);

BOOST_AUTO_TEST_CASE(ForwardBase)
{
    {
        TestPointer ptr = createTest();
        BOOST_CHECK(ptr);
        checkTestCount(1);
    }
    checkTestCount(0);
    {
        TestPointer ptr = createTest();
        TestPointer ptr2 = createTest();
        checkTestCount(2);
        ptr2 = ptr;
        ptr.reset();
        checkTestCount(1);
        ptr2.reset();
        checkTestCount(0);
    }
}

struct Test: yandex::contest::IntrusivePointeeBase
{
    Test() { ++count; }
    ~Test() { --count; }

    static std::size_t count;
};

std::size_t Test::count = 0;

TestPointer createTest()
{
    return TestPointer(new Test);
}

void checkTestCount(const std::size_t count)
{
    BOOST_CHECK_EQUAL(Test::count, count);
}

YANDEX_CONTEST_INTRUSIVE_PTR_DEFINE(Test)

BOOST_AUTO_TEST_SUITE_END() // IntrusivePointerHelper

#include <yandex/contest/detail/ForwardFooter.hpp>
