#ifndef HASH_DOUBLE_H
#define HASH_DOUBLE_H
#pragma once
#include "HashProbing.h"
#include "helper.h"

template <typename K, typename V>
class DoubleHashing : public HashTableProbing<K,V> {
    int prime;
public:
    DoubleHashing(int size)
        : HashTableProbing<K,V>(
              size, [this](int base, int step, K key){
                  return base + step * (prime - (key % prime));
              }),
          prime(helper::nextPrime(size / 2)) {}
};
#endif