#include <boost/test/unit_test.hpp>

#include <ww/lru_cache.hpp>

using namespace ww;

BOOST_AUTO_TEST_SUITE(lru_cache_test_suite)

BOOST_AUTO_TEST_CASE(lru_cache_test_case_1)
{
    lru_cache<int, int> cache(3);
}

BOOST_AUTO_TEST_SUITE_END()

// vim:set sw=4 ts=4 et:
