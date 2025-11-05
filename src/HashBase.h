#ifndef HASH_BASE_H
#define HASH_BASE_H
#include <vector>
#include <iostream>

template <typename K, typename V>
class HashTableBase {
public:
    virtual bool insert(const K& key, const V& value) = 0;
    virtual bool search(const K& key, V& out) = 0;
    virtual void erase(const K& key) = 0;

    virtual double loadFactor() const = 0;
    virtual int maxCluster() const = 0;
    virtual double avgCluster() const = 0;

    virtual ~HashTableBase() = default;
};
#endif