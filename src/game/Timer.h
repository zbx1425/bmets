#pragma once
#include <vector>
#include <chrono>

namespace bmets::game {

class Timer {
 public:
  std::vector<int> durations;
  std::chrono::high_resolution_clock::time_point last_clock;
  int last_id;
  int size;
  int total;

  Timer(int size);

  void clear();
  void begin(int id);
  void end();
};

}