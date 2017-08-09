#if !defined(_WW_CONTAINER_HPP_)
#define _WW_CONTAINER_HPP_

#include <memory>
#include <string>

#include <ww/lru_cache.hpp>

namespace ww {

/**
 * A container of a fixed size that accepts as input data any sort of key-value
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
 * A basic usage of this class is shown in the test/container.cpp file. Please
 * refer to it if you want to see examples.
 *
 * @see ww::lru_cache
 */
template <typename K, typename V> class
container
{
public:
    typedef typename lru_cache<K, V>::size_type size_type;

private:
    lru_cache<K, V> cache;

public:
    /**
     * Initializes the container and the internal LRU cache with a maximum size
     * of 'size'.
     *
     * @param size The size of the LRU cache.
     */
    container(size_type max_size)
        : cache(max_size)
    {
    }

    ~container()
    {
    }

public:
    /**
     * Add an entry to the cache. Overwrite if the key had already been added
     * before. If the cache is full discard the least used entry and return
     * accordingly.
     *
     * @param k The key, the index of the entry to be added.
     * @param v The value of the new entry.
     *
     * @return false if an entry from the cache had to be discarded.
     */
    bool
    add(const K &k, const V &v)
    {
        return cache.set(k, v);
    }

    /**
     * Retrieves a value from the container indexed by the key passed as parameter.
     *
     * If the key is not found in the cache a negative response will be emitted.
     *
     * @param[in] k The key, the index of the entry to be added.
     * @return A pointer to the value found in the cache.
     *
     * @return false in case the entry is not found in the cache.
     */
    V *
    get(const K &k)
    {
        return cache.get(k);
    }

};

}

#endif // !defined(_WW_CONTAINER_HPP_)

// vim:set sw=4 ts=4 et:
