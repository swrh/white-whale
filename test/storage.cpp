#include <memory>
#include <string>

#include <boost/test/unit_test.hpp>

#include <ww/storage.hpp>

using namespace std;

using namespace ww;

BOOST_AUTO_TEST_SUITE(storage_test_suite)

BOOST_AUTO_TEST_CASE(storage_test_case_example_1)
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

    // CREATE mycontainer key=string value=int N=3
    shared_ptr<abstract_storage> mycontainer = make_shared<storage<string, int>>(3);
    BOOST_REQUIRE(mycontainer != nullptr);

    // ADD mycontainer "mykey1" 42
    success = mycontainer->query_add("\"mykey1\"", "42");
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());

    success = mycontainer->query_get("\"mykey1\"", result);
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "42");

    // ADD mycontainer "mykey2" 17
    success = mycontainer->query_add("\"mykey2\"", "17");
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());

    // ADD mycontainer "mykey3" 19
    success = mycontainer->query_add("\"mykey3\"", "19");
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());

    success = mycontainer->query_get("\"mykey1\"", result);
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "42");

    success = mycontainer->query_get("\"mykey2\"", result);
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "17");

    success = mycontainer->query_get("\"mykey3\"", result);
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "19");

    // ADD mycontainer "mykey4" 0 // clear the key "mykey1"
    success = mycontainer->query_add("\"mykey4\"", "0");
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());

    // GET mycontainer "mykey1" // no entry found
    success = mycontainer->query_get("\"mykey1\"", result);
    BOOST_REQUIRE_MESSAGE(!success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "");

    success = mycontainer->query_get("\"mykey2\"", result);
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "17");

    success = mycontainer->query_get("\"mykey3\"", result);
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "19");

    success = mycontainer->query_get("\"mykey4\"", result);
    BOOST_REQUIRE_MESSAGE(success, mycontainer->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "0");

    // DESTRUCT mycontainer
    mycontainer.reset();
}

BOOST_AUTO_TEST_CASE(storage_test_case_example_2)
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

    // CREATE container2 key=float value=string N=2
    shared_ptr<abstract_storage> container2 = make_shared<storage<float, string>>(2);
    BOOST_REQUIRE(container2 != nullptr);

    // ADD container2 4.2 "val1"
    success = container2->query_add("4.2", "\"val1\"");
    BOOST_REQUIRE_MESSAGE(success, container2->get_error_string());

    // ADD container2 1.7 "val2"
    success = container2->query_add("1.7", "\"val2\"");
    BOOST_REQUIRE_MESSAGE(success, container2->get_error_string());

    success = container2->query_get("1.7", result);
    BOOST_REQUIRE_MESSAGE(success, container2->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "\"val2\"");

    // GET container2 4.2 // return "val1"
    success = container2->query_get("4.2", result);
    BOOST_REQUIRE_MESSAGE(success, container2->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "\"val1\"");

    // ADD container2 0.0 "val3" // clear the key 1.7
    success = container2->query_add("0.0", "\"val3\"");
    BOOST_REQUIRE_MESSAGE(success, container2->get_error_string());

    success = container2->query_get("1.7", result);
    BOOST_REQUIRE_MESSAGE(!success, container2->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "");

    // ADD container2 3.14 "val4" // clear the key 4.2
    success = container2->query_add("3.14", "\"val4\"");
    BOOST_REQUIRE_MESSAGE(success, container2->get_error_string());

    success = container2->query_get("4.2", result);
    BOOST_REQUIRE_MESSAGE(!success, container2->get_error_string());
    BOOST_REQUIRE_EQUAL(result, "");

    // DESTRUCT container2
    container2.reset();
}

BOOST_AUTO_TEST_SUITE_END()

// vim:set sw=4 ts=4 et:
