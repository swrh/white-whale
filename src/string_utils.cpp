#include <ww/string_utils.hpp>

#include <limits>
#include <string>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

namespace ww {

/**
 * Convert from argument string to string.
 *
 * Simply removes the beginning and trailing double quotes. Fails if none is
 * found.
 *
 * @return false if failed for some reason.
 */
template <> bool
string_utils::from_string<string>(const string &s, string &t)
{
    if (s.size() < 2 || *s.begin() != '"' || *s.rbegin() != '"')
        return false;
    t.assign(s.begin() + 1, s.end() - 1);
    return true;
}

/**
 * Convert from a string to argument string.
 *
 * Simply adds double quotes in the beginning and the end of the output string.
 *
 * @return true always.
 */
template <> bool
string_utils::to_string<string>(const string &t, string &s) {
    s = "\"" + t + "\"";
    return true;
}

/**
 * Convert from argument string to int.
 *
 * Uses ::strtol(3).
 *
 * @return false if failed for some reason.
 */
template <> bool
string_utils::from_string<int>(const string &s, int &t)
{
    char *endptr = nullptr;
    long int l = ::strtol(&s[0], &endptr, 0);
    if (endptr == nullptr || *endptr != '\0')
        return false;

    if (l > numeric_limits<int>::max() || l < numeric_limits<int>::min())
        return false;

    t = static_cast<int>(l);
    return true;
}

/**
 * Convert from int to argument string.
 *
 * Uses ::snprintf(3).
 *
 * @return true always.
 */
template <> bool
string_utils::to_string<int>(const int &t, string &s) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", t);
    s = buf;
    return true;
}

/**
 * Convert from float to argument string.
 *
 * Uses ::snprintf(3).
 *
 * @return false if failed for some reason.
 */
template <> bool
string_utils::to_string<float>(const float &t, string &s) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%f", t);
    s = buf;
    return true;
}

/**
 * Convert from argument string to float.
 *
 * Uses ::strtol(3).
 *
 * @return false if failed for some reason.
 */
template <> bool
string_utils::from_string<float>(const string &s, float &t) {
    char *endptr = nullptr;
    t = strtof(s.c_str(), &endptr);
    if (endptr == nullptr || *endptr != '\0')
        return false;
    if (t == HUGE_VALF)
        return false;
    return true;
}

}

// vim:set sw=4 ts=4 et:
