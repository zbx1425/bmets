#pragma once
#include "Spline.h"
#include <glm/glm.hpp>

namespace bmets::math {

  class SPMainL;

  // Spline part for the vertical part of the main track.
  class SPChildL {
  public:
    double begin = 0;
    double length = DBL_MAX;
    Spline<SPMainL>* parent;

    // NAN here means this value is not yet determined.
    // X1, X2, Radius are guranteed to be non-NAN after baking.
    // X2 are guranteed to be NAN before baking.
    double x1, x2 = DBL_NAN, radius;

    // Create a default node used at the frontmost of the spline.
    SPChildL() { 
      is_default = true;
      x1 = x2 = radius = 0;
    }

    // Create an value node
    SPChildL(Spline<SPMainL>* parent, double x1, double radius) {
      this->parent = parent;
      this->x1 = x1;
      this->radius = radius;
    }

    glm::dvec2 value_at(double location);
    double dir_at(double location);
    void bake(SPChildL *last, SPChildL *next);

  private:
    bool is_default = false;
  };
}