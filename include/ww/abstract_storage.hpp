#if !defined(_WW_ABSTRACT_STORAGE_HPP_)
#define _WW_ABSTRACT_STORAGE_HPP_

#include <string>

namespace ww {

/**
 * The abstract class (interface) of a storage.
 *
 * For more details please refer to the ww::storage<> template class
 * documentation.
 *
 * @see ww::storage<>
 */
class
abstract_storage
{
public:
    /**
     * The description of the last error occurred.
     */
    enum class operation_error {
        /// Success, no error occurred.
        success,
        /// The key passed as string is invalid (invalid format).
        invalid_key_string,
        /// The value passed as string is invalid (invalid format).
        invalid_value_string,
        /// Could not convert the data stored in the cache to string.
        could_not_convert_data,
        /// The referred entry could not be found.
        entry_not_found,
    };

protected:
    operation_error error;

    abstract_storage();

    /**
     * Set the error code as the detail of the last error ocurred.
     *
     * This method should only be used at the end of each public method to
     * describe what error ocurred.
     */
    void set_error(operation_error e);

public:
    virtual ~abstract_storage();

    /**
     * Get the operation error code of the last error occurred.
     *
     * @return The last operation error code.
     */
    operation_error get_error() const;

    /**
     * Get the operation error description of the last error occurred.
     *
     * @return The last operation error description.
     */
    std::string get_error_string() const;

    /**
     * Add an entry to the cache, or overwrite it if the key is already in use.
     *
     * As string parsing errors might occur, the usage of the get_error() and
     * get_error_string() is recommended.
     *
     * @param key The key, the index of the entry to be added.
     * @param value The value of the new entry.
     *
     * @return false in case an string parsing error occur. For more details
     * the get_error() or get_error_string() should be called.
     */
    virtual bool query_add(const std::string &key, const std::string &value) = 0;

    /**
     * Retrieves a value from the storage indexed by the key passed as parameter.
     *
     * If the key is not found in the cache a negative response will be emitted.
     *
     * As string parsing errors might occur, the usage of the get_error() and
     * get_error_string() is recommended.
     *
     * @param[in] key The key, the index of the entry to be added.
     * @param[out] value The contents of the requested entry will be written in
     * this variable.
     *
     * @return false in case an string parsing error occur or the entry is not
     * found. For more details the get_error() or get_error_string() should be
     * called.
     */
    virtual bool query_get(const std::string &key, std::string &value) = 0;
};

}

#endif // !defined(_WW_ABSTRACT_STORAGE_HPP_)

// vim:set sw=4 ts=4 et:
