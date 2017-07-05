#if !defined(_WW_CONTAINER_HPP_)
#define _WW_CONTAINER_HPP_

#include <ww/abstract_storage.hpp>
#include <ww/storage.hpp>

#include <map>
#include <memory>
#include <string>

namespace ww {

/**
 * The main container class: store multiple tables/containers/storages of
 * key-value entries. These entries are stored and recycled using an LRU cache
 * replacement policy.
 *
 * The data will be stored using the lru_cache<> class. It basically stores the
 * data up to a limit using an LRU cache replacement policy. For more
 * information please check the lru_cache<> class documentation.
 *
 * This class is the main interface of this library. To use it you probably
 * need to call just the main methods: create(), add(), get(), destruct() and
 * get_error() or get_error_string().
 *
 * Please refer to the documentation of each method for more information.
 */
class
container
{
public:
    enum class operation_error {
        success,
        unknown_error,
        invalid_key_or_value_type,
        container_already_exists,
        container_not_found,
        storage_error,
    };

private:
    typedef std::map<std::string, storage_ptr> map_type;

    map_type storages;

private:
    storage_weak_ptr last_failing_storage;
    operation_error error;

    /**
     * Set the error code as the detail of the last error ocurred.
     *
     * This method should only be used at the end of each public method to
     * describe what error ocurred.
     */
    void set_error(operation_error e);

public:
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

public:
    /**
     * Create a new named container if not created yet.
     *
     * This method will create a new container of key and value types specified
     * in the K and V template parameters, and name and size specified in the
     * method arguments.
     *
     * @param name The name of the new container.
     * @param n The size of the new container.
     *
     * @return false in case the container already exists.
     */
    template <typename K, typename V> bool
    create(const std::string &name, uint64_t n)
    {
        map_type::iterator it = storages.find(name);
        if (it != storages.end()) {
            set_error(operation_error::container_already_exists);
            return false;
        }

        storages[name] = std::make_shared<storage<K, V>>(n);
        set_error(operation_error::success);
        return true;
    }

    /**
     * Add an entry to the container, or overwrite it if the key is already in
     * use.
     *
     * As string parsing errors might occur, the usage of the get_error() and
     * get_error_string() is recommended.
     *
     * @param name The name of the new container.
     * @param key The key, the index of the entry to be added.
     * @param value The value of the new entry.
     *
     * @return false in case an string parsing error occur. For more details
     * the get_error() or get_error_string() should be called.
     */
    bool add(const std::string &name, const std::string &key, const std::string &value);

    /**
     * Retrieves a value from the container indexed by the key passed as parameter.
     *
     * If the key is not found in the container a negative response will be emitted.
     *
     * As string parsing errors might occur, the usage of the get_error() and
     * get_error_string() is recommended.
     *
     * @param[in] name The name of the new container.
     * @param[in] key The key, the index of the entry to be added.
     * @param[out] value The contents of the requested entry will be written in
     * this variable.
     *
     * @return false in case an string parsing error occur or the entry is not
     * found. For more details the get_error() or get_error_string() should be
     * called.
     */
    bool get(const std::string &name, const std::string &key, std::string &value);

    /**
     * Destroy the named container passsed as argument.
     *
     * @param name The name of the container to be destroyed.
     *
     * @return false in case the container is not found.
     */
    bool destruct(const std::string &name);

};

}

#endif // !defined(_WW_CONTAINER_HPP_)

// vim:set sw=4 ts=4 et:
