#ifndef GENERATOR_H
#define GENERATOR_H
#include <vector>
#include <utility>
#include <random>
#include <algorithm>

namespace Gen {

    // Sinh ra M cặp (key, value) tăng dần: (0, 0), (1, 1), (2, 2), ...
    template <typename K = int, typename V = int>
    std::vector<std::pair<K, V>> sequentialKV(int M) {
        std::vector<std::pair<K, V>> data;
        data.reserve(M);
        for (int i = 0; i < M; ++i)
            data.emplace_back(i, i);
        return data;
    }

    // Sinh ra M cặp (key, value) ngẫu nhiên trong [0, maxKey)
    template <typename K = int, typename V = int>
    std::vector<std::pair<K, V>> randomKV(int M, int maxKey = 1000000) {
        std::vector<std::pair<K, V>> data;
        data.reserve(M);
        std::mt19937 rng(std::random_device{}());
        std::uniform_int_distribution<K> dist(0, maxKey);
        for (int i = 0; i < M; ++i)
            data.emplace_back(dist(rng), dist(rng));
        return data;
    }

    // Sinh ra M khóa ngẫu nhiên không trùng (cho bài test tìm kiếm)
    template <typename K = int>
    std::vector<K> uniqueKeys(int M, int maxKey = 1000000) {
        std::vector<K> keys(maxKey);
        for (int i = 0; i < maxKey; ++i) keys[i] = i;
        std::shuffle(keys.begin(), keys.end(), std::mt19937(std::random_device{}()));
        keys.resize(M);
        return keys;
    }

}
#endif