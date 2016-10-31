
#include "sort.hpp"
#include <vector>
#include <algorithm>
#include <chrono>

int main() {
  std::ranlux24 gen;
  std::vector<int> x(0x100000);

  printf("par::sort\n");
  for (int i = 0; i != 5; ++i) {
    gen.seed();
    std::generate(x.begin(), x.end(), [&gen]() { return (int)gen(); });
    auto start = std::chrono::high_resolution_clock::now();
    par::sort(x.begin(), x.end(), [](int a, int b) { return a < b; });
    auto end = std::chrono::high_resolution_clock::now();
    printf("%10dns\n", (int)std::chrono::nanoseconds(end - start).count());
  }

  printf("std::sort\n");
  for (int i = 0; i != 5; ++i) {
    gen.seed();
    std::generate(x.begin(), x.end(), [&gen]() { return (int)gen(); });
    auto start = std::chrono::high_resolution_clock::now();
    std::sort(x.begin(), x.end(), [](int a, int b) { return a < b; });
    auto end = std::chrono::high_resolution_clock::now();
    printf("%10dns\n", (int)std::chrono::nanoseconds(end - start).count());
  }
}

