#ifndef BENCHMARK_H
#define BENCHMARK_H
#include "HashBase.h"
#include <chrono>
#include <iostream>

struct BenchResult {
    long long insertTime{}, searchTime{}, deleteTime{};
};

template <typename Table>
BenchResult benchmark(Table& table, const std::vector<std::pair<int,int>>& data) {
    using namespace std::chrono;
    BenchResult res;

    auto t1 = high_resolution_clock::now();
    for (auto& [k,v] : data) table.insert(k,v);
    auto t2 = high_resolution_clock::now();
    res.insertTime = duration_cast<microseconds>(t2-t1).count();

    int dummy;
    t1 = high_resolution_clock::now();
    for (auto& [k,v] : data) table.search(k,dummy);
    t2 = high_resolution_clock::now();
    res.searchTime = duration_cast<microseconds>(t2-t1).count();

    t1 = high_resolution_clock::now();
    for (auto& [k,v] : data) table.erase(k);
    t2 = high_resolution_clock::now();
    res.deleteTime = duration_cast<microseconds>(t2-t1).count();

    return res;
}
#endif