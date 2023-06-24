#define CacheCPP_Included
#include "Cache.h"
using namespace std;

template <typename ValueType>
Cache<ValueType>::Cache(int maxSize) {
    /* TODO: Delete this line, delete the next line, and implement this member function. */
    (void) maxSize;
}

template <typename ValueType>
Cache<ValueType>::~Cache() {
    /* TODO: Delete this line and implement this function. */
}

template <typename ValueType>
void Cache<ValueType>::put(const std::string& key, const ValueType& value) {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    (void) key;
    (void) value;
}

template <typename ValueType>
bool Cache<ValueType>::containsKey(const std::string& key) const {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    (void) key;
    return false;
}

template <typename ValueType>
ValueType Cache<ValueType>::get(const std::string& key) {
    /* TODO: Delete this line, delete the next two lines, and implement this member function. */
    (void) key;
    return {};
}
