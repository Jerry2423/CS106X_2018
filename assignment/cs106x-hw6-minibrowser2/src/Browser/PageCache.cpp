#include "PageCache.h"
using namespace std;

PageCache::PageCache(int maxSize) {
    maximumSize = maxSize;
    compressed = false;
}

void PageCache::put(const string& key, RawPage value) {
    if (compressed) value.compressPage();
    else value.uncompressPage();

    int index = indexOf(key);
    if (index != -1) {
        CacheElem n = cache[index];
        cache.remove(index);
        n.value = value;
        cache.add(n);
    } else {
        if (cache.size() == maximumSize) {
            cache.removeFront();
        }

        cache.add(CacheElem({key, value}));
    }
}

int PageCache::indexOf(const string& key) const {
    for (int i = 0; i < cache.size(); i++) {
        if (cache[i].key == key) {
            return i;
        }
    }

    return -1;
}

bool PageCache::containsKey(const string& key) const {
    return indexOf(key) != -1;
}

RawPage PageCache::get(const string& key) {
    int index = indexOf(key);
    if (index == -1) {
        error("No element found");
        return {};
    } else {
        CacheElem n = cache[index];
        cache.remove(index);
        cache.add(n);
        RawPage pageToReturn = n.value;
        pageToReturn.uncompressPage();
        return pageToReturn;
    }
}

tuple<size_t, size_t> PageCache::getCompressionSpaceSavings() {
    size_t totalBytes = 0;
    size_t compressedBytes = 0;
    for (CacheElem e : cache) {
        totalBytes += e.value.decompressedByteSize;
        compressedBytes += e.value.text.length();
    }

    return make_tuple(totalBytes, compressedBytes);
}

void PageCache::shouldCompress(bool compress) {
    for (CacheElem& e : cache) {
        if (compress) {
            e.value.compressPage();
        } else {
            e.value.uncompressPage();
        }
    }

    this->compressed = compress;
}

