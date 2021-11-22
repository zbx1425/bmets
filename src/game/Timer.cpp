#include "Timer.h"

using namespace bmets::game;
using namespace std::chrono;

Timer::Timer(int size) {
  this->size = size;
  durations.resize(size);
}

void Timer::clear() {
  durations.clear();
  durations.resize(size);
  total = 0;
  last_id = -1;
}

void Timer::begin(int id) {
  if (last_id >= 0) {
    int duration = duration_cast<milliseconds>(high_resolution_clock::now() - last_clock).count();
    durations[last_id] += duration;
    total += duration;
  }
  last_id = id;
  last_clock = high_resolution_clock::now();
}

void Timer::end() {
  if (last_id >= 0) {
    int duration = duration_cast<milliseconds>(high_resolution_clock::now() - last_clock).count();
    durations[last_id] += duration;
    total += duration;
  }
  last_id = -1;
}