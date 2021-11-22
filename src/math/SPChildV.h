#pragma once
#include "Spline.h"

namespace bmets::math {

  class SPMainV;

  // Spline part for the vertical part of the main track.
  class SPChildV {
  public:
    double begin = 0;
    double length = DBL_MAX;
    Spline<SPMainV>* parent;

    // NAN here means this value is not yet determined.
    // Y1, Y2, Radius are guranteed to be non-NAN after baking.
    // Y2 are guranteed to be NAN before baking.
    double y1, y2 = DBL_NAN, radius;

    // Create a default node used at the frontmost of the spline.
    SPChildV() { 
      is_default = true;
      y1 = y2 = radius = 0;
    }

    // Create an value node
    SPChildV(Spline<SPMainV>* parent, double y1, double radius) {
      this->parent = parent;
      this->y1 = y1;
      this->radius = radius;
    }

    double value_at(double location);
    double dir_at(double location);
    void bake(SPChildV *last, SPChildV *next);

  private:
    bool is_default = false;
  };
}