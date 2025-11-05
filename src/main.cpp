#include "HashLinear.h"
#include "HashQuadratic.h"
#include "HashDouble.h"
#include "Benchmark.h"
#include "Generator.h"

int main() {
    int M = 10000;
    auto data = Gen::sequentialKV(M);

    LinearProbing<int,int> linear(20000);
    QuadraticProbing<int,int> quadratic(20000);
    DoubleHashing<int,int> dbl(20000);

    auto r1 = benchmark(linear, data);
    auto r2 = benchmark(quadratic, data);
    auto r3 = benchmark(dbl, data);

    std::cout << "Insert times: " << r1.insertTime << ", "
              << r2.insertTime << ", " << r3.insertTime << "\n";
}
