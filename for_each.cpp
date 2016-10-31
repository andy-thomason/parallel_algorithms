
#include "for_each.hpp"
#include <vector>
#include <algorithm>
#include <chrono>

int main() {
  std::vector<int> x(0x100000);

  printf("par::for_each\n");
  for (int i = 0; i != 5; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    par::for_each(x.begin(), x.end(), [](int &r) { r = 0; });
    auto end = std::chrono::high_resolution_clock::now();
    printf("%10ldns\n", std::chrono::nanoseconds(end - start).count());
  }

  printf("\nstd::for_each\n");
  for (int i = 0; i != 5; ++i) {
    auto start = std::chrono::high_resolution_clock::now();
    std::for_each(x.begin(), x.end(), [](int &r) { r = 0; });
    auto end = std::chrono::high_resolution_clock::now();
    printf("%10ldns\n", std::chrono::nanoseconds(end - start).count());
  }
}


