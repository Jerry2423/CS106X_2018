#include "CacheTests.h"
#include "Cache.h"
#include <chrono>
using namespace std;
ENABLE_TESTS();

ADD_TEST("Cache works like a Map when capacity isn't exceeded.") {
    Cache<int> cache(137);

    cache.put("A", 1);
    cache.put("B", 2);
    cache.put("C", 3);
    cache.put("D", 4);

    expect(cache.containsKey("A"));
    expect(cache.containsKey("B"));
    expect(cache.containsKey("C"));
    expect(cache.containsKey("D"));

    expect(cache.get("A") == 1);
    expect(cache.get("B") == 2);
    expect(cache.get("C") == 3);
    expect(cache.get("D") == 4);
}

ADD_TEST("Only remembers last 4 items if capacity is 4.") {
    Cache<int> cache(4);

    cache.put("A", 1);
    cache.put("B", 2);
    cache.put("C", 3);
    cache.put("D", 4);
    cache.put("E", 5);
    cache.put("F", 6);

    expect(cache.get("F") == 6);
    expect(cache.get("E") == 5);
    expect(cache.get("D") == 4);
    expect(cache.get("C") == 3);

    expect(!cache.containsKey("B"));
    expect(!cache.containsKey("A"));

    expectError(cache.get("A"));
    expectError(cache.get("B"));
}

ADD_TEST("Evicts least-recently-accessed element, not the least-recently-added element.") {
    Cache<int> cache(3);

    cache.put("A", 1);
    cache.put("B", 2);
    cache.put("C", 3);

    /* Look up A. The internal order should now be A (newest), C, B (oldest) */
    expect(cache.get("A") == 1);

    /* This should evict B, the oldest key. */
    cache.put("D", 4);

    /* Confirm that A, C, and D are present and that D is not. */
    expect(cache.get("A") == 1);
    expectError(cache.get("B"));
    expect(cache.get("C") == 3);
    expect(cache.get("D") == 4);
}

/* Utility function that, given a number, maps it to a string. */
string keyFor(int n) {
    string result;
    while (n > 32) {
        result += 'A' + char(n % 32);
        n /= 32;
    }
    return result + char('A' + n);
}

ADD_TEST("With HashMap, Cache operations should be fast, even at a large size.") {
    const int kCacheSize = 10000;
    Cache<int> cache(kCacheSize);

    /* Load up the cache, in order. */
    for (int i = 0; i < kCacheSize; i++) {
        cache.put(keyFor(i), i);
    }

    /* Start timing things. */
    auto start = chrono::high_resolution_clock::now();

    /* Look up elements in reverse order. This will be extremely slow (O(n) per iteration)
     * unless the cache has a map providing access into the internal list.
     */
    const int kNumRounds = 10;
    for (int round = 0; round < kNumRounds; round++) {
        for (int i = kCacheSize - 1; i >= 0; i--) {
            expect(cache.get(keyFor(i)) == i);
        }
    }

    auto elapsed = chrono::high_resolution_clock::now() - start;
    auto timeInMillis = chrono::duration_cast<chrono::milliseconds>(elapsed).count();

    /* This should take no more than five seconds. */
    const double kTimeCutoff = 5000; // ms
    expect(timeInMillis <= kTimeCutoff);
}

/* This custom type remembers how many objects of its type have been constructed. */
struct Counter {
    Counter()                    { instances++; }
    Counter(const Counter&)      { instances++; }
    Counter(Counter&&)           { instances++; }
    ~Counter()                   { instances--; }
    Counter& operator= (const Counter &) = default;

    static int instances;
};
int Counter::instances = 0;

ADD_TEST("Cache should free the memory used by its cells.") {
    /* Make a bunch of caches, adding and removing things as we see fit, and
     * then check that there are no instances left.
     */
    expect(Counter::instances == 0);

    const int kNumRounds = 10;
    const int kCacheSize = 25;
    const int kNumElems  = 100;
    for (int round = 0; round < kNumRounds; round++) {
        Cache<Counter> cache(kCacheSize);
        for (int i = 0; i < kNumElems; i++) {
            cache.put(keyFor(i), {});
        }
    }

    expect(Counter::instances == 0);
}

/* TODO: Add a bunch of your own custom tests here! Use this syntax:
 *
 *    ADD_TEST("Description of your test") {
 *        // code for your test
 *    }
 */
