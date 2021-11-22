#pragma once
#include <glm/glm.hpp>
#include "Spline.h"

namespace bmets::math {

  // Spline part for the lateral part of the main track.
  class SPMainL {
  public:
    double begin = 0;
    double length = DBL_MAX;

    // NAN here means this value is not yet determined.
    // Curv1/2, Dir1 are guranteed to be non-NAN after baking.
    // Dir2 can be non-NAN if it is the final part and it is not straight.
    // Curv2, Dir1/2 are guranteed to be NAN before baking.
    // Curv1 can be non-NAN before baking if this node has been assigned a radius.
    // Thus, in the function "bake", only next->curv1 can be used.
    double curv1 = DBL_NAN, curv2 = DBL_NAN;
    double dir1 = DBL_NAN, dir2 = DBL_NAN;
    bool is_default = false;

    // Create a default node used at the frontmost of the spline.
    SPMainL() { 
      is_default = true;
      dir1 = dir2 = 0;
      curv1 = curv2 = 0;
    }

    // Create an transition node
    SPMainL(short i) {
      curv1 = DBL_NAN;
      ixfunc = i;
    }

    // Create an value node
    SPMainL(double radius, short i) {
      if (std::isinf(radius)) {
        curv1 = 0;
      } else if (radius == 0) {
        // BVE5 silently ignores this
        curv1 = 0;
      } else {
        curv1 = 1 / radius;
      }
      ixfunc = i;
    }

    glm::dvec2 value_at(double location);
    double dir_at(double location);
    void bake(SPMainL *last, SPMainL *next);

  private:
    glm::dvec2 value1;
    double gamma = DBL_NAN;
    short ixfunc;
  };
}
