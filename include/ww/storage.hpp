#if !defined(_WW_STORAGE_HPP_)
#define _WW_STORAGE_HPP_

#include <ww/abstract_storage.hpp>
#include <ww/lru_cache.hpp>
#include <ww/string_utils.hpp>

#include <memory>
#include <string>

namespace ww {

/**
 * A storage of a fixed size that accepts as input data any sort of key-value
 * pair.
 *
 * This class is a template that accepts two parameters of any type of data to
 * be stored. The template parameters are the key and the value types.
 *
 * The data will be stored using the lru_cache<> class. It basically stores the
 * data up to a limit using an LRU cache replacement policy. For more
 * information please check the lru_cache<> class documentation.
 *
 * There are basically two types of interfaces in this class: the native and
 * the query interface. Both interfaces have only two methods: an ADD method
 * and a GET method. The query interface, implemented by the query_{add,get}()
 * methods, receives and returns data only as strings, and should be used only
 * when the type of the data being stored or retrieved is unknown or cannot be
 * specified. As parsing errors might occur, the usage of the get_error() and
 * get_error_string() is recommended. The native interface, implemented by the
 * add() and get() methods, is faster and receives only native types as
 * parameters. This is the recommended interface.
 *
 * A basic usage of this class is shown in the test/storage.cpp file. Please
 * refer to it if you want to see examples.
 *
 * @see ww::lru_cache
 */
template <typename K, typename V> class
storage
: public abstract_storage
{
private:
    lru_cache<K, V> cache;

public:
    /**
     * Initializes the storage and the internal LRU cache with a fixed type
     * of size 'size'.
     *
     * @param size The size of the LRU cache.
     */
    storage(uint64_t size)
        : cache(size)
    {
    }

public:
    /**
     * Add an entry to the cache, or overwrite it if the key is already in use.
     *
     * @param k The key, the index of the entry to be added.
     * @param v The value of the new entry.
     */
    void
    add(const K &k, const V &v)
    {
        cache.set(k, v);
    }

    /**
     * Retrieves a value from the storage indexed by the key passed as parameter.
     *
     * If the key is not found in the cache a negative response will be emitted.
     *
     * @param[in] k The key, the index of the entry to be added.
     * @param[out] v A pointer that will be set to the value found in the
     * cache. nullptr in case it isn't found.
     *
     * @return false in case the entry is not found in the cache.
     */
    bool
    get(const K &k, V *&v)
    {
        if (!cache.get(k, v)) {
            set_error(operation_error::entry_not_found);
            return false;
        }
        return true;
    }

public:
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
    bool
    query_add(const std::string &key, const std::string &value)
    {
        K k;
        V v;

        if (!string_utils::from_string(key, k)) {
            set_error(operation_error::invalid_key_string);
            return false;
        }

        if (!string_utils::from_string(value, v)) {
            set_error(operation_error::invalid_value_string);
            return false;
        }

        set_error(operation_error::success);
        add(k, v);
        return true;
    }

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
    bool
    query_get(const std::string &key, std::string &value)
    {
        K k;
        V *v;

        if (!string_utils::from_string(key, k)) {
            value = "";
            set_error(operation_error::invalid_key_string);
            return false;
        }

        if (!get(k, v)) {
            value = "";
            return false;
        }

        if (!string_utils::to_string(*v, value)) {
            value = "";
            set_error(operation_error::could_not_convert_data);
            return false;
        }

        set_error(operation_error::success);
        return true;
    }
};

typedef std::shared_ptr<abstract_storage> storage_ptr;
typedef std::weak_ptr<abstract_storage> storage_weak_ptr;

}

#endif // !defined(_WW_STORAGE_HPP_)

// vim:set sw=4 ts=4 et:
