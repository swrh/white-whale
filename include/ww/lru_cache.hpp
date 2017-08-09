#if !defined(_WW_LRU_CACHE_HPP_)
#define _WW_LRU_CACHE_HPP_

#include <list>
#include <map>

namespace ww {

/**
 * A simple implementation of a key-value container using an LRU cache
 * replacement policy.
 *
 * This class stores values indexed by keys and discards the least used values.
 * The usage is based on the last time a key has been used with the set()/get()
 * methods. When a key is used its priority raises and when the cache is full
 * and a new key is added (using the set() method) the least used key is
 * removed from the cache.
 *
 * To achieve the LRU policy this class stores all items into a std::list,
 * ordered by the most recently used keys, and index the items using a
 * std::map. This combination removes the need to search for items in the list
 * when a access is requested and reduces the complexity to the same of the
 * std::map. As it usually is a binary tree, the complexity should be something
 * around O(log n).
 */
template <typename K, typename V> class
lru_cache
{
public:
    typedef std::list<std::pair<K, V>> list_type;
    typedef std::map<K, typename list_type::iterator> map_type;
    typedef std::size_t size_type;

    const size_type max_size;

protected:
    list_type pairs;
    map_type table;

public:
    lru_cache(size_type max_size)
        : max_size(max_size)
    {
    }

    /**
     * Add or replace an entry in the cache.
     *
     * @param[in] key The key to index the value.
     * @param[in] value The value to be stored.
     *
     * @return false if an entry from the cache had to be discarded.
     */
    bool
    set(const K &key, const V &value)
    {
        typename map_type::iterator it = table.find(key);
        if (it != table.end()) {
            // This key already exists and will be overwritten.
            pairs.erase(it->second);
            table.erase(it);
        }

        pairs.push_front(make_pair(key, value));
        table.insert(make_pair(key, pairs.begin()));

        if (table.size() <= max_size)
            return true;

        // The cache reached its limit and we must discard the least used item.
        table.erase(pairs.rbegin()->first);
        pairs.pop_back();

        return false;
    }

    /**
     * Retrieve a value from the cache.
     *
     * @param[in] key The key to index the value.
     *
     * @return A pointer to the value found.
     */
    V *
    get(const K &key)
    {
        typename map_type::iterator t = table.find(key);
        if (t == table.end())
            return nullptr;

        pairs.splice(pairs.begin(), pairs, t->second);
        return &t->second->second;
    }
};

}

#endif // !defined(_WW_LRU_CACHE_HPP_)

// vim:set sw=4 ts=4 et:
