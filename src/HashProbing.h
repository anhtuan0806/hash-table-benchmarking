#ifndef HASH_PROBING_H
#define HASH_PROBING_H
#include "HashBase.h"
#include <cmath>
#include <functional>

enum SlotState { EMPTY, OCCUPIED, DELETED };

template <typename K, typename V>
struct Entry {
    K key{};
    V value{};
    SlotState state{EMPTY};
};

template <typename K, typename V>
class HashTableProbing : public HashTableBase<K, V> {
protected:
    std::vector<Entry<K, V>> table;
    int sz{};
    int used{};
    std::function<int(int,int,K)> probeFunc;  // Hàm probe tuỳ theo loại hash

public:
    HashTableProbing(int size, std::function<int(int,int,K)> func)
        : sz(size), used(0), probeFunc(std::move(func)) {
        table.assign(sz, {});
    }

    bool insert(const K& key, const V& val) override {
        int base = key % sz;
        for (int step = 0; step < sz; ++step) {
            int idx = probeFunc(base, step, key) % sz;
            if (table[idx].state != OCCUPIED) {
                table[idx] = {key, val, OCCUPIED};
                used++;
                return true;
            }
            if (table[idx].key == key) {
                table[idx].value = val;
                return true;
            }
        }
        return false;
    }

    bool search(const K& key, V& out) override {
        int base = key % sz;
        for (int step = 0; step < sz; ++step) {
            int idx = probeFunc(base, step, key) % sz;
            if (table[idx].state == EMPTY) return false;
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                out = table[idx].value;
                return true;
            }
        }
        return false;
    }

    void erase(const K& key) override {
        int base = key % sz;
        for (int step = 0; step < sz; ++step) {
            int idx = probeFunc(base, step, key) % sz;
            if (table[idx].state == EMPTY) return;
            if (table[idx].state == OCCUPIED && table[idx].key == key) {
                table[idx].state = DELETED;
                used--;
                return;
            }
        }
    }

    double loadFactor() const override {
        return (double)used / sz;
    }

    int maxCluster() const override { /* tương tự code cũ */ return 0; }
    double avgCluster() const override { return 0; }
};
#endif