#pragma once
#include "Spline.h"

namespace bmets::math {

  // Spline part for the vertical part of the main track.
  class SPMainV {
  public:
    double begin = 0;
    double length = DBL_MAX;

    // NAN here means this value is not yet determined.
    // Tan1, Tan2 are guranteed to be non-NAN after baking.
    // Tan2 are guranteed to be NAN before baking.
    // Tan1 can be non-NAN before baking if this node has been assigned a gradient.
    // Thus, in the function "bake", only next->tan1 can be used.
    double tan1 = DBL_NAN, tan2 = DBL_NAN;

    // Create a default node used at the frontmost of the spline.
    SPMainV() { 
      is_default = true;
      tan1 = tan2 = 0;
    }

    // Create an transition node
    SPMainV(short i) {
      tan1 = DBL_NAN;
      ixfunc = i;
    }

    // Create an value node
    SPMainV(double tg, short i) {
      tan1 = tg / 1000;
      ixfunc = i;
    }

    double value_at(double location);
    double dir_at(double location);
    void bake(SPMainV *last, SPMainV *next);

  private:
    double theta1 = DBL_NAN, theta2 = DBL_NAN;
    short ixfunc;
    bool is_default = false;
    double value1;
  };
}