#ifndef HASH_QUADRATIC_H
#define HASH_QUADRATIC_H
#include "HashProbing.h"

template <typename K, typename V>
class QuadraticProbing : public HashTableProbing<K,V> {
public:
    QuadraticProbing(int size)
        : HashTableProbing<K,V>(
              size, [](int base, int step, K){ return base + step * step; }) {}
};
#endif