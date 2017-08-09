#include <memory>
#include <string>

#include <boost/test/unit_test.hpp>

#include <ww/container.hpp>

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

    int *result;
    shared_ptr<container<string, int>> mycontainer;

    // CREATE mycontainer key=string value=int N=3
    mycontainer = make_shared<container<string, int>>(3);
    BOOST_REQUIRE(mycontainer != nullptr);

    // ADD mycontainer "mykey1" 42
    BOOST_REQUIRE(mycontainer->add("mykey1", 42));

    // ADD mycontainer "mykey2" 17
    BOOST_REQUIRE(mycontainer->add("mykey2", 17));

    // ADD mycontainer "mykey3" 19
    BOOST_REQUIRE(mycontainer->add("mykey3", 19));

    // ADD mycontainer "mykey4" 0 // clear the key "mykey1"
    BOOST_REQUIRE(!mycontainer->add("mykey4", 0));

    // GET mycontainer "mykey1" // no entry found
    result = mycontainer->get("mykey1");
    BOOST_REQUIRE(result == nullptr);

    // DESTRUCT mycontainer
    mycontainer.reset();
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

    string *result;
    shared_ptr<container<float, string>> container2;

    // CREATE container2 key=float value=string N=2
    container2 = make_shared<container<float, string>>(2);
    BOOST_REQUIRE(container2 != nullptr);

    // ADD container2 4.2 "val1"
    BOOST_REQUIRE(container2->add(4.2, "val1"));

    // ADD container2 1.7 "val2"
    BOOST_REQUIRE(container2->add(1.7, "val2"));

    // GET container2 4.2 // return "val1"
    result = container2->get(4.2);
    BOOST_REQUIRE(result != nullptr);
    BOOST_REQUIRE(*result == "val1");

    // ADD container2 0.0 "val3" // clear the key 1.7
    BOOST_REQUIRE(!container2->add(0.0, "val3"));

    // ADD container2 3.14 "val4" // clear the key 4.2
    BOOST_REQUIRE(!container2->add(3.14, "val4"));

    // DESTRUCT container2
    container2.reset();
}

BOOST_AUTO_TEST_SUITE_END()

// vim:set sw=4 ts=4 et:
