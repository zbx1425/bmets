#include "SPMainL.h"
#include <glm/gtx/rotate_vector.hpp>
#include "Fresnel.h"
#include "../util/FmtException.h"
#include <string>

using namespace bmets::math;

static double sign(double a) { return a > 0.0 ? 1.0 : -1.0; }

static glm::dvec2 operator*(glm::dvec2 a, double b) {
  return {a.x * b, a.y * b};
}

glm::dvec2 SPMainL::value_at(double location) {
  if (is_default) return { location, 0 };
  if (length == 0) return value1;
  double s = location - begin;
  // TODO: Sine
  if (ixfunc != 0 && gamma != 0) {
    // Linear interpolation
    double sa, ca, sb, cb;
    fresnl((curv1 + gamma * s) / std::sqrt(M_PI * std::abs(gamma)), &sa, &ca);
    fresnl(curv1 / std::sqrt(M_PI * std::abs(gamma)), &sb, &cb);
    glm::dvec2 cs1 = glm::rotate(glm::dvec2{std::sqrt(M_PI / std::abs(gamma)), 0}, dir1 - pow(curv1, 2) / 2 / gamma);
    glm::dvec2 cs2 = { sign(gamma) * (ca - cb), sa - sb };
    glm::dvec2 cs1mcs2 = { cs1.x * cs2.x - cs1.y * cs2.y, cs1.y * cs2.x + cs1.x * cs2.y };
    return value1 + cs1mcs2;
  } else {
    // Constant
    if (curv1 == 0) {
      // Straight
      return value1 + glm::rotate(glm::dvec2 { location - begin, 0 }, dir1);
    } else {
      double theta = s * curv1;
      glm::dvec2 offset = { sin(theta) / curv1, (1 - cos(theta)) / curv1 };
      return value1 + glm::rotate(offset, dir1);
    }
  }
}

double SPMainL::dir_at(double location) {
  if (is_default) return 0;
  if (length == 0) return dir1;
  double s = location - begin;
  // TODO: Sine
  if (ixfunc != 0 && gamma != 0) {
    // Linear
    return gamma * s * s / 2 + curv1 * s + dir1;
  } else {
    // Constant
    return curv1 * s + dir1;
  }
}

void SPMainL::bake(SPMainL *last, SPMainL *next) {
  if (last == nullptr) {
    // The first default part does not need baking.
    if (!is_default) throw FmtException("Internal: Bad spline description (front).");
    return;
  }

  // Determine Curv1.
  if (std::isnan(curv1)) {
    // This is an transition node.
    // The initial curvature is inferred from the last node.
    if (last != nullptr && !std::isnan(last->curv2)) {
      curv1 = last->curv2;
    } else {
      throw FmtException("Internal: Bad spline description (transition) in MainL.");
    }
  }

  // Determine Curv2.
  if (next != nullptr) {
    curv2 = next->curv1;
    if (std::isnan(curv2)) {
      // The next node is an transition node.
      // Thus, the current node cannot have interpolation.
      curv2 = curv1;
    }
  } else {
    // This is the last node.
    // Thus, there is nothing to interpolate.
    curv2 = curv1;
  }

  // Calculate Gamma.
  gamma = 1 * (curv2 - curv1) / length;
  // No need for interpolation if the curve is constant.
  if (curv1 == curv2) ixfunc = 0;

  // Determine Value1.
  value1 = last->value_at(begin);
  if (std::isnan(value1.x) || std::isnan(value1.y))
    throw FmtException("Internal: Spline calculation resulted in NaN (Lateral position) at %lf", begin);

  // Determine Dir1.
  dir1 = last->dir2;
  if (std::isnan(dir1))
    throw FmtException("Internal: Bad spline description (Lateral direction) from %lf", begin);

  // Determine Dir2.
  if (next != nullptr) {
    dir2 = dir_at(begin + length);
    if (std::isnan(dir1))
      throw FmtException("Internal: Spline calculation resulted in NaN (Lateral direction) at %lf", begin + length);
  } else {
    // This is the last node.
    if (curv1 == 0.0) {
      dir2 = dir1;
    } else {
      // It rotates infinitely. We cannot acquire the final direction.
      dir2 = DBL_NAN;
    }
  }
}