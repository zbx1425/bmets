#pragma once
#include <cmath>
#include <vector>
#include <cassert>
#include "../util/FmtException.h"

#ifndef DBL_NAN
#define DBL_NAN std::numeric_limits<double>().quiet_NaN()
#endif
#ifndef DBL_INF
#define DBL_INF std::numeric_limits<double>().infinity()
#endif
#ifndef DBL_MAX
#define DBL_MAX std::numeric_limits<double>().max()
#endif

namespace bmets::math {

  template <typename TPart>
  class Spline {
  public:
    std::vector<TPart> parts;
  public:
    mutable int lookup_ptr = 0;

  public:
    void push_back(TPart part, double location) {
      part.begin = location;
      part.length = DBL_MAX;
      if (parts.size() > 0) {
        TPart* last = &parts.back();
        if (last->begin > location) throw FmtException("Invalid part insertion sequence.");
        last->length = location - last->begin;
        parts.emplace_back(part);
      } else {
        parts.emplace_back(part);
      }
    }

    void clear() {
      parts.clear();
      lookup_ptr = 0;
      push_back(TPart{ }, -DBL_MAX);
    }

    void bake() {
      for (int i = 0; i < parts.size(); i++) {
        parts[i].bake(i > 0 ? &parts[i - 1] : nullptr, i < parts.size() - 1 ? &parts[i + 1] : nullptr);
      }
    }

    decltype(std::declval<TPart>().value_at(0)) value_at(double location) {
      assert(parts.size() > 0 && location >= parts[0].begin);
      while (lookup_ptr > 0 && parts[lookup_ptr].begin > location) lookup_ptr--;
      while (lookup_ptr < parts.size() - 1 && parts[lookup_ptr + 1].begin < location) lookup_ptr++;
      return parts[lookup_ptr].value_at(location);
    }

    decltype(std::declval<TPart>().dir_at(0)) dir_at(double location) {
      assert(parts.size() > 0 && location >= parts[0].begin);
      while (lookup_ptr > 0 && parts[lookup_ptr].begin > location) lookup_ptr--;
      while (lookup_ptr < parts.size() - 1 && parts[lookup_ptr + 1].begin < location) lookup_ptr++;
      return parts[lookup_ptr].dir_at(location);
    }

    Spline() {
      clear();
    }
  };
}
