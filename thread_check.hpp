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

#include <vector>
#include <assert.h>
#include <algorithm>

// Very simple example of a class to detect data races.
// The class only reports success or failure for a particular class.
namespace par {
  template<class Type>
  class thread_check {
    bool flag_ = false;
  public:
    void lock() {
      if (flag_) {
        printf("thread_check for %s failed\n", typeid(Type).name());
        exit(1);
      }
      flag_ = true;
    }

    void unlock() {
      flag_ = false;
    }
  };
}

