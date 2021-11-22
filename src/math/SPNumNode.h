#pragma once
#include "Spline.h"

namespace bmets::math {

  // Spline part for an interpolated sequence of numbers.
  class SPNumNode {
  public:
    double begin = 0;
    double length = DBL_MAX;

    // NAN here means this value is not yet determined.
    // Value1, Value2 are guranteed to be non-NAN after baking.
    // Value2 is guranteed to be NAN before baking.
    // Value1 can be non-NAN if this node has a value.
    double value1 = DBL_NAN, value2 = DBL_NAN;

    // Create a default node used at the frontmost of the spline.
    SPNumNode() { 
      is_default = true;
      value1 = value2 = 0;
    }

    // Create an value node
    SPNumNode(double value, short ixfunc) {
      this->value1 = value;
      this->ixfunc = ixfunc;
    }

    // Create an transition node
    SPNumNode(short ixfunc) {
      this->ixfunc = ixfunc;
    }

    double value_at(double location);
    double dir_at(double location);
    void bake(SPNumNode *last, SPNumNode *next);

  private:
    short ixfunc;
    bool is_default = false;
  };
}