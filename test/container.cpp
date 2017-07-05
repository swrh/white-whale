#include <ww/container.hpp>

#include <boost/test/unit_test.hpp>

using namespace std;

using namespace ww;

BOOST_AUTO_TEST_SUITE(container_test_suite)

BOOST_AUTO_TEST_CASE(container_test_case_example_1)
{
    /*
     * CREATE mycontainer key=string value=int N=3
     * ADD mycontainer "mykey1" 42
     * ADD mycontainer "mykey2" 17
     * ADD mycontainer "mykey3" 19
     * ADD mycontainer "mykey4" 0 // clear the key "mykey1"
     * GET mycontainer "mykey1" // no entry found
     * DESTRUCT mycontainer
     */

    bool success;
    string result;

    container c;

    // CREATE mycontainer key=string value=int N=3
    success = c.create<string, int>("mycontainer", 3);
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // ADD mycontainer "mykey1" 42
    success = c.add("mycontainer", "\"mykey1\"", "42");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // ADD mycontainer "mykey2" 17
    success = c.add("mycontainer", "\"mykey2\"", "17");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // ADD mycontainer "mykey3" 19
    success = c.add("mycontainer", "\"mykey3\"", "19");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // ADD mycontainer "mykey4" 0 // clear the key "mykey1"
    success = c.add("mycontainer", "\"mykey4\"", "0");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // GET mycontainer "mykey1" // no entry found
    success = c.get("mycontainer", "\"mykey1\"", result);
    BOOST_REQUIRE_MESSAGE(!success, c.get_error_string());
    BOOST_REQUIRE_EQUAL(result, "");
    // DESTRUCT mycontainer
    success = c.destruct("mycontainer");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
}

BOOST_AUTO_TEST_CASE(container_test_case_example_2)
{
    /*
     * CREATE container2 key=float value=string N=2
     * ADD container2 4.2 "val1"
     * ADD container2 1.7 "val2"
     * GET container2 4.2 // return "val1"
     * ADD container2 0.0 "val3" // clear the key 1.7
     * ADD container2 3.14 "val4" // clear the key 4.2
     * DESTRUCT container2
     */

    bool success;
    string result;

    container c;

    // CREATE container2 key=float value=string N=2
    success = c.create<float, string>("container2", 2);
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // ADD container2 4.2 "val1"
    success = c.add("container2", "4.2", "\"val1\"");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // ADD container2 1.7 "val2"
    success = c.add("container2", "1.7", "\"val2\"");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // GET container2 4.2 // return "val1"
    success = c.get("container2", "4.2", result);
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    BOOST_REQUIRE_EQUAL(result, "\"val1\"");
    // ADD container2 0.0 "val3" // clear the key 1.7
    success = c.add("container2", "0.0", "\"val3\"");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // ADD container2 3.14 "val4" // clear the key 4.2
    success = c.add("container2", "3.14", "\"val4\"");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
    // DESTRUCT container2
    success = c.destruct("container2");
    BOOST_REQUIRE_MESSAGE(success, c.get_error_string());
}

BOOST_AUTO_TEST_SUITE_END()

// vim:set sw=4 ts=4 et:
