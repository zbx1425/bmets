#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "Spline.h"
#include "SPNumNode.h"
#include "SPModel.h"
#include "SPMainL.h"
#include "SPMainV.h"
#include "SPChildL.h"
#include "SPChildV.h"

namespace bmets::math {

  class Followable {
  public:
    static const int TILT_NONE = 0;
    static const int TILT_GRADIENT = 1;
    static const int TILT_CANT = 2;
    static const int TILT_GRADIENT_CANT = 3;
    
    short curve_ix_func = 1;
    double gauge = 1.435;

    virtual glm::dvec3 pos_at(double location) = 0;
    virtual glm::mat4 model_mat_at(double location, 
      double x, double y, double z, double rx, double ry, double rz,
      int tilt, double span) = 0;
  };

  template <class TPartL, class TPartV>
  class Track : public Followable {
  public:
    Spline<TPartL> l_spline;
    Spline<TPartV> v_spline;
    Spline<SPNumNode> cant_spline;

    Track() {
      clear();
    }

    void bake() {
      l_spline.bake();
      v_spline.bake();
      cant_spline.bake();
    }

    void clear() {
      l_spline.clear();
      v_spline.clear();
      cant_spline.clear();
    }

    virtual glm::dvec3 pos_at(double location) {
      glm::vec2 lPos = l_spline.value_at(location);
      double vPos = v_spline.value_at(location);
      return glm::dvec3 { lPos.y, vPos, -lPos.x };
    }

    virtual glm::mat4 model_mat_at(double location, 
      double x, double y, double z, double rx, double ry, double rz,
      int tilt, double span) {
        if (span == 0.0) span = 1.0;
        glm::dvec3 posA = pos_at(location), posB = pos_at(location + span);
        if (!(tilt & TILT_GRADIENT)) posB.y = posA.y;
        glm::dmat4 matTrack = glm::inverse(glm::lookAt(posA, posB, glm::dvec3 { 0, 1, 0 }));
        glm::dmat4 matModel = glm::translate( glm::dvec3 { x, y, -z } ) * glm::eulerAngleYZX(-ry, rz, -rx);

        double cant = cant_spline.value_at(location);
        bool hasCant = (tilt & TILT_CANT) && cant != 0.0;
        if (hasCant) {
          return matTrack * glm::rotate(cant, glm::dvec3 { 0, 0, -1 }) * matModel;
        } else {
          return matTrack * matModel;
        }
    }
  };

  class MainTrack : public Track<SPMainL, SPMainV> {
  public:
    Spline<SPModel> bg_spline;

    double last_pitch = 0.0, last_radius = DBL_INF, last_cant = 0.0;
    int l_tx_begin_line = -1, v_tx_begin_line = -1;

    MainTrack() {
      clear();
    }

    void clear() {
      Track::clear();
      bg_spline.clear();
    }

    void bake() {
      Track::bake();
      bg_spline.bake();
    }
  };

  class ChildTrack : public Track<SPChildL, SPChildV> {
  public:
    double last_x = 0.0, last_y = 0.0, last_x_radius = DBL_INF, last_y_radius = DBL_INF, last_cant = 0.0;
    int c_tx_begin_line = -1;

    ChildTrack() {
      clear();
    }

    void clear() {
      Track::clear();
    }
  };
}