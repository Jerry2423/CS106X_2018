#pragma once

#include <string>

/**
 * A type representing a cache. This class works similarly to the Map interface, except that
 * there's an upper limit to how many key/value pairs can be stored at one time. If that amount
 * is exceeded, the least-recently-used (LRU) key/value pair is removed (evicted) from the
 * cache to make room for the new element.
 *
 * Any time an element is accessed - whether that's a lookup by key, or a contains query, etc. -
 * that element is marked as being accessed so that its priority for removal drops.
 */
template <typename ValueType> class Cache {
public:
    /**
     * Constructs a new Cache of the specified size. You can assume that the maximum
     * size is positive.
     *
     * @param maxSize The maximum number of elements to keep in the cache at any point in time.
     */
    Cache(int maxSize);

    /**
     * Frees all memory allocated by this structure.
     */
    ~Cache();

    /**
     * Inserts a new key/value pair into the page cache.
     *
     * If the key already exists in the cache, this operation should act as though the key was
     * looked up, but should otherwise have no effect.
     *
     * If the key did not already exist in the cache, you should add it to the cache, then
     * evict the oldest element if the cache is full.
     *
     * This function should run in time O(1).
     *
     * @param key The key.
     * @param value The associated value.
     */
    void put(const std::string& key, const ValueType& value);

    /**
     * Returns whether there is a value associated with the specified key in the cache. Note that
     * an element that was added with put() is not guaranteed to still be present when calling
     * get(), since it may have been evicted.
     *
     * This function should run in time O(1).
     *
     * @param key The key to look up.
     * @return Whether it's present in the cache.
     */
    bool containsKey(const std::string& key) const;

    /**
     * Returns the value associated with a given key. If the key isn't
     * present, you should report an error by calling the error() function.
     *
     * Looking up an element accesses it, making it less likely to be deleted in the
     * future.
     *
     * This function should run in time O(1).
     *
     * @param key The key to look up.
     * @return The value associated with that key.
     */
    ValueType get(const std::string& key);


private:
    /* Type representing a node in the doubly-linked list portion of the Cache. Feel free
     * to add whatever fields you'd like.
     */
    struct Node {
        std::string key; // std::string because this is a header file.
        ValueType   value;
        Node*       prev;
        Node*       next;
    };

    // TODO: add any helper functions and instance variables you need

};

/* Because Cache is a template class, we have to do some Weird Sorcery in order to get
 * the .cpp file to compile properly.
 */
#ifndef CacheCPP_Included
#include "Cache.cpp"
#endif
