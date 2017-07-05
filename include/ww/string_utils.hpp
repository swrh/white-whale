#if !defined(_WW_STRING_UTILS_HPP_)
#define _WW_STRING_UTILS_HPP_

#include <string>

namespace ww {

/**
 * A simple utility class to convert strings to types (int, float, etc) and
 * vice versa.
 *
 * This class must not be instantiated.
 */
class
string_utils
{
private:
    string_utils();

public:
    /**
     * Converts a string to the specified type T.
     *
     * @param[in] s The input string.
     * @param[out] t The result of the conversion.
     */
    template <typename T> static bool from_string(const std::string &s, T &t);

    /**
     * Converts the value of type T to a string.
     *
     * @param[in] t The input value.
     * @param[out] s The result of the conversion.
     */
    template <typename T> static bool to_string(const T &t, std::string &s);
};

}

#endif // !defined(_WW_STRING_UTILS_HPP_)

// vim:set sw=4 ts=4 et:
