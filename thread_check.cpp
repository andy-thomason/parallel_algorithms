////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2016
//
// Example of a low-overhead thread check.
//
// Mutexes, even if implemented as spin locks, can be very costly.
//
// It is common to use excessive mutexes to solve unexpected multithreaded crashes
// in code.
//
// Another method is to replace selected mutexes with a thread safety check.
// This will report if the objects protected really are accessed by separate threads.
//
////////////////////////////////////////////////////////////////////////////////

#include "thread_check.hpp"
#include <mutex>
#include <future>

class A {
  std::vector<int> ints;

  // Replace this with std::mutex check; only when the thread check fails.
  // std::mutex check;
  par::thread_check<A> check;
public:
  void push(int a) {
    std::lock_guard<decltype(check)> lock(check);
    ints.push_back(a);
  }
};

class B {
  std::vector<float> floats;
  par::thread_check<B> check;
public:
  void push(float a) {
    std::lock_guard<decltype(check)> lock(check);
    floats.push_back(a);
  }
};

int main() {
  A a;
  auto fn = [&a]() {
    B b;
    for (int i = 0; i != 10000; ++i) {
      a.push(1);
      b.push(1.0f);
    }
  };

  auto t1 = std::async(std::launch::async, fn);
  auto t2 = std::async(std::launch::async, fn);

  t1.wait(); t2.wait();
}

