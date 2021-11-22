#pragma once
#include "Spline.h"

namespace bmets::render {
  class Model;
}

namespace bmets::math {

  // Spline part for the vertical part of the main track.
  class SPModel {
  public:
    double begin = 0;
    double length = DBL_MAX;

    // nullptr means not yet determined.
    bmets::render::Model* model;

    // Create a default node used at the frontmost of the spline.
    SPModel() {
      model = nullptr;
    }

    // Create an value node
    SPModel(bmets::render::Model* model) {
      this->model = model;
    }

    bmets::render::Model* value_at(double location) {
      return model;
    }

    double dir_at(double location) {
      return 0.0;
    }

    void bake(SPModel *last, SPModel *next) {
      if (model == nullptr && next != nullptr && next->model != nullptr) {
        this->model = next->model;
      }
    }
  };
}