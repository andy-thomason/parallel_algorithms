////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2016
// Simple example of a parallel sort
//
////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <algorithm>
#include "for_each.hpp"

// note this is not ideal. Smarter algoithms are possible but it is simple.
namespace par {
  template <class Fn, class FwdIt, int ChunkSize=0x10000, int NumCPUs=8>
  void sort(FwdIt b, FwdIt e, Fn func) {
    // partition into roughly ChunkSize chunks.
    size_t size = e - b;
    std::vector<std::pair<FwdIt, FwdIt>> to_do;
    std::vector<std::pair<FwdIt, FwdIt>> chunks;
    to_do.push_back(std::make_pair(b, e));
    while (!to_do.empty()) {
      auto &back = to_do.back();
      FwdIt cb = back.first, ce = back.second;
      to_do.pop_back();
      if (ce - cb < ChunkSize) {
        chunks.push_back(std::make_pair(cb, ce));
      } else {
        auto pivot = cb[(ce-cb)/2];
        auto m = std::partition(cb, ce, [pivot](const auto &val) {
          return val < pivot;
        });
        if (m != ce && cb != m) {
          to_do.push_back(std::make_pair(m, ce));
          to_do.push_back(std::make_pair(cb, m));
        } else {
          // prevent hangs... 
          chunks.push_back(std::make_pair(cb, ce));
        }
      }
    }

    std::atomic<size_t> start{0};
    std::array<std::future<void>, NumCPUs> futures;
    for (auto &f : futures) {
      f = std::async(std::launch::async, [&chunks, &start, &func]() {
        for (;;) {
          size_t idx = start++;
          if (idx >= chunks.size()) break;
          auto &ch = chunks[idx];
          std::sort(ch.first, ch.second, func);
        }
      });
    }
    for (auto &f : futures) f.wait();
  }
}

