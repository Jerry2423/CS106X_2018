#include "CacheTests.h"
#include "PageCache.h"
#include "Downloader.h"
#include <chrono>
using namespace std;
ENABLE_TESTS();

ADD_TEST("Cache works like a Map when capacity isn't exceeded.") {
    PageCache cache(137);

    RawPage a({"a", {}});
    RawPage b({"b", {}});
    RawPage c({"c", {}});
    RawPage d({"d", {}});

    cache.put("A", a);
    cache.put("B", b);
    cache.put("C", c);
    cache.put("D", d);

    expect(cache.containsKey("A"));
    expect(cache.containsKey("B"));
    expect(cache.containsKey("C"));
    expect(cache.containsKey("D"));

    expect(cache.get("A") == a);
    expect(cache.get("B") == b);
    expect(cache.get("C") == c);
    expect(cache.get("D") == d);
}

ADD_TEST("Only remembers last 4 items if capacity is 4.") {
    PageCache cache(4);

    RawPage a({"a", {}});
    RawPage b({"b", {}});
    RawPage c({"c", {}});
    RawPage d({"d", {}});
    RawPage e({"e", {}});
    RawPage f({"f", {}});

    cache.put("A", a);
    cache.put("B", b);
    cache.put("C", c);
    cache.put("D", d);
    cache.put("E", e);
    cache.put("F", f);

    expect(cache.get("F") == f);
    expect(cache.get("E") == e);
    expect(cache.get("D") == d);
    expect(cache.get("C") == c);

    expect(!cache.containsKey("B"));
    expect(!cache.containsKey("A"));

    expectError(cache.get("A"));
    expectError(cache.get("B"));
}

ADD_TEST("Evicts least-recently-accessed element, not the least-recently-added element.") {
    PageCache cache(3);

    RawPage a({"a", {}});
    RawPage b({"b", {}});
    RawPage c({"c", {}});
    RawPage d({"d", {}});

    cache.put("A", a);
    cache.put("B", b);
    cache.put("C", c);

    /* Look up A. The internal order should now be A (newest), C, B (oldest) */
    expect(cache.get("A") == a);

    /* This should evict B, the oldest key. */
    cache.put("D", d);

    /* Confirm that A, C, and D are present and that D is not. */
    expect(cache.get("A") == a);
    expectError(cache.get("B"));
    expect(cache.get("C") == c);
    expect(cache.get("D") == d);
}
