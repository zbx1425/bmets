#include "SPNumNode.h"
#include "../util/FmtException.h"

using namespace bmets::math;

double SPNumNode::value_at(double location) {
  if (is_default) return value1;
  if (length == 0) return value1;
  double s = location - begin;
  // TODO: Sine
  if (ixfunc == 1 || ixfunc == 2) {
    return (value2 - value1) * s / length + value1;
  } else {
    return value1;
  }
}

double SPNumNode::dir_at(double location) {
  if (is_default) return 0;
  if (length == 0) return 0;
  double s = location - begin;
  // TODO: Sine
  if (ixfunc == 1 || ixfunc == 2) {
    return (value2 - value1) / length;
  } else {
    return 0;
  }
}

void SPNumNode::bake(SPNumNode *last, SPNumNode *next) {
  if (last == nullptr) {
    if (!is_default) throw FmtException("Internal: Bad spline description (front).");

    if (next != nullptr && !std::isnan(next->value1)) {
      // Try to acquire the value of the next node.
      value1 = value2 = next->value1;
    }
    return;
  }

  // Determine Value1.
  if (std::isnan(value1)) {
    // This is an transition node.
    // The initial value is inferred from the last node.
    if (last != nullptr && !std::isnan(last->value1)) {
      value1 = last->value1;
    } else {
      throw FmtException("Internal: Bad spline description (transition) in NumNode.");
    }
  }

  // Determine Value2.
  if (ixfunc != 0 && next != nullptr && !std::isnan(next->value1)) {
    value2 = next->value1;
  } else {
    value2 = value1;
  }
  
  // No need for interpolation if the value is constant.
  if (value1 == value2) ixfunc = 0;
}