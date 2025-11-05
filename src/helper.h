#ifndef HELPER_H
#define HELPER_H
#include <cmath>

// Namespace helper chứa các hàm tiện ích dùng chung
namespace helper {

    // Kiểm tra một số có phải là số nguyên tố không
    inline bool isPrime(int n) {
        if (n <= 1) return false;
        if (n <= 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (int i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0)
                return false;
        }
        return true;
    }

    // Trả về số nguyên tố nhỏ nhất >= n
    inline int nextPrime(int n) {
        if (n <= 2) return 2;
        while (!isPrime(n)) ++n;
        return n;
    }

}
#endif