#ifndef HASH_LINEAR_H
#define HASH_LINAER_H
#include "HashProbing.h"

template <typename K, typename V>
class LinearProbing : public HashTableProbing<K,V> {
public:
    LinearProbing(int size)
        : HashTableProbing<K,V>(
              size, [](int base, int step, K){ return base + step; }) {}
};
#endif