#include "SPMainV.h"
#include "../util/FmtException.h"

using namespace bmets::math;

double SPMainV::value_at(double location) {
  if (is_default) return 0;
  if (length == 0) return value1;
  double s = location - begin;
  if (ixfunc == 1) {
    // Conic
    return value1 + (tan1 + dir_at(location)) * s / 2;
  } else if (ixfunc == 2) {
    // Circular
    // From kobushi-trackviewer
    return value1 
      + length / (theta2 - theta1) * cos(theta1)
      - length / (theta2 - theta1) * cos((theta2 - theta1) / length * s + theta1);
  } else {
    // Linear
    return value1 + tan1 * s;
  }
}

double SPMainV::dir_at(double location) {
  if (is_default) return 0;
  if (length == 0) return tan1;
  double s = location - begin;
  if (std::isnan(tan1)) return std::numeric_limits<double>().quiet_NaN();
  if (ixfunc == 1) {
    // Conic
    return tan1 + (tan2 - tan1) * (s / length);
  } else if (ixfunc == 2) {
    // Circular
    return tan(theta1 + (theta2 - theta1) * (s / length));
  } else {
    // Linear
    return tan1;
  }
}

void SPMainV::bake(SPMainV *last, SPMainV *next) {
  if (last == nullptr) {
    // The first default part does not need baking.
    if (!is_default) throw FmtException("Internal: Bad spline description (front).");
    return;
  }

  // Determine Tan1.
  if (std::isnan(tan1)) {
    // This is an transition node.
    // The initial tangent is inferred from the last node.
    if (last != nullptr && !std::isnan(last->tan2)) {
      tan1 = last->tan2;
    } else {
      throw FmtException("Internal: Bad spline description (transition) in MainV.");
    }
  }

  // Determine Tan2.
  if (next != nullptr) {
    tan2 = next->tan1;
    if (std::isnan(tan2)) {
      // The next node is an transition node.
      // Thus, the current node cannot have any interpolation.
      tan2 = tan1;
    }
  } else {
    // This is the last node.
    tan2 = tan1;
  }
  
  // Calculate Theta.
  theta1 = atan(tan1); theta2 = atan(tan2);
  // No need for interpolation if the curve is constant.
  if (tan1 == tan2) ixfunc = 0;

  // Determine Value1.
  value1 = last->value_at(begin);
}