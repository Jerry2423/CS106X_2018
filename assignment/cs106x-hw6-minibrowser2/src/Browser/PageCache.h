#pragma once

#include <string>
#include "vector.h"
#include "Downloader.h"

/**
 * A type representing a cache of page names to their text. This class works similarly to the Map interface,
 * except that there's an upper limit to how many key/value pairs can be stored at one time.
 * If that amount is exceeded, the least-recently-used (LRU) key/value pair is removed (evicted)
 * from the cache to make room for the new element.
 *
 * Any time an element is accessed - whether that's a lookup by key, adding, etc. -
 * that element is marked as being accessed so that its priority for removal drops.
 *
 * This cache can also compress and decompress the values it stores.  If it is in the compressed
 * state, it will auto-compress all values (RawPages) before inserting them into the cache.
 * It always returns uncompressed results.
 */
class PageCache {
public:
    /**
     * Constructs a new Cache of the specified size. Assumes that the maximum
     * size is positive.
     *
     * @param maxSize The maximum number of elements to keep in the cache at any point in time.
     */
    PageCache(int maxSize);

    /**
     * Inserts a new key/value pair into the page cache.  Makes a copy of the value, and compresses
     * it before inserting if the cache is compressed.
     *
     * If the key already exists in the cache, this operation updates its value, then
     * reflects that it is most recently accessed.
     *
     * If the key did not already exist in the cache, it is added to the cache, and
     * evicts the oldest element if the cache is full.
     *
     * @param key The key.
     * @param value The associated value.
     */
    void put(const std::string& key, RawPage value);

    /**
     * Returns whether there is a value associated with the specified key in the cache. Note that
     * an element that was added with put() is not guaranteed to still be present when calling
     * get(), since it may have been evicted.
     *
     * @param key The key to look up.
     * @return Whether it's present in the cache.
     */
    bool containsKey(const std::string& key) const;

    /**
     * Returns the value associated with a given key. If the key isn't
     * present, this function reports an error by calling the error() function.
     *
     * Looking up an element accesses it, making it less likely to be deleted in the
     * future.
     *
     * If the cache is compressed, decompresses the value first before returning it.
     *
     * @param key The key to look up.
     * @return The value associated with that key.
     */
    RawPage get(const std::string& key);

    /**
     * Compresses or decompresses all data in the cache, and ensures that all future
     * values are compressed or not.
     *
     * @param compress true if we should compress, false if we should decompress.
     */
    void shouldCompress(bool compress);

    /**
     * Returns the amount of space used by compressed entries currently in the
     * cache, vs. uncompressed size.
     *
     * @return the total number of uncompressed bytes used, and the total number
     * of compressed bytes used.  (e.g. 400 bytes, 200 bytes would mean that
     * originally the content is 400 bytes, but now it is compressed to 200 bytes).
     */
    std::tuple<size_t, size_t> getCompressionSpaceSavings();


private:
    // A type to store a key/value pair
    struct CacheElem {
        std::string key;
        RawPage value;
    };

    Vector<CacheElem> cache;
    int maximumSize;
    int indexOf(const std::string& key) const;
    bool compressed;
};
