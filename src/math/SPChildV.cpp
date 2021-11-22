#include "SPChildV.h"
#include "SPMainV.h"
#include "../util/FmtException.h"

using namespace bmets::math;

static double rel_pos(double L, double radius, double a, double b, double x) {
  if (L == 0) {
    return b;
  } else if (radius != 0 && radius != DBL_INF) {
    double sinTheta = std::sqrt(L * L + (b - a) * (b - a)) / (2 * radius);
    if (std::abs(sinTheta <= 1)) {
      double tau = atan((b - a) / L);
      double theta = 2 * asin(sinTheta);
      double phiA = theta / 2 - tau;
      double x0 = radius * sin(phiA);
      double y0 = a + radius * cos(phiA);
      return y0 - radius * cos(asin((x - x0) / radius));
    } else {
      return (b - a) / L * x + a;
    }
  } else {
    return (b - a) / L * x + a;
  }
}

double SPChildV::value_at(double location) {
  double x = location - begin;
  return rel_pos(length, radius, y1, y2, x) + parent->value_at(location);
}

double SPChildV::dir_at(double location) {
  return DBL_NAN; // No calculation available so far
}

void SPChildV::bake(SPChildV *last, SPChildV *next) {
  if (last == nullptr) {
    // The first default part does not need baking.
    if (!is_default) throw FmtException("Internal: Bad spline description (front).");
    if (next != nullptr) {
      y1 = y2 = next->y1;
    } else {
      y1 = y2 = 0;
    }
    return;
  }

  // Determine Y2.
  if (next != nullptr) {
    y2 = next->y1;
  } else {
    y2 = y1;
  }
}