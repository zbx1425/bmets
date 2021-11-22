#include "SPChildL.h"
#include "SPMainL.h"
#include "../util/FmtException.h"
#include <glm/gtx/rotate_vector.hpp>

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

glm::dvec2 SPChildL::value_at(double location) {
  double x = location - begin;
  glm::dvec2 relPos = { 0, rel_pos(length, radius, x1, x2, x) };
  return glm::rotate(relPos, parent->dir_at(location)) + parent->value_at(location);
}

double SPChildL::dir_at(double location) {
  return DBL_NAN; // No calculation available so far
}

void SPChildL::bake(SPChildL *last, SPChildL *next) {
  if (last == nullptr) {
    // The first default part does not need baking.
    if (!is_default) throw FmtException("Internal: Bad spline description (front).");
    if (next != nullptr) {
      x1 = x2 = next->x1;
    } else {
      x1 = x2 = 0;
    }
    return;
  }

  // Determine X2.
  if (next != nullptr) {
    x2 = next->x1;
  } else {
    x2 = x1;
  }
}