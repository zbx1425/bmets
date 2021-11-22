#include "Map.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include "../render/Manager.h"

using namespace bmets::game;

void Repeater::begin(Map* map, double location, bmets::math::IFollowable* track, 
      double x, double y, double z, double rx, double ry, double rz,
      int tilt, double span, double interval, std::vector<bmets::render::ModelList*> structures) {
  if (has_begun) apply(map, location);
  has_begun = true;
  begin_location = location;
  this->track = track;
  this->x = x;
  this->y = y;
  this->z = z;
  this->rx = rx;
  this->ry = ry;
  this->rz = rz;
  this->tilt = tilt;
  this->span = span;
  this->interval = interval;
  this->structures = std::move(structures);
}

void Repeater::end(Map* map, double location) {
  if (has_begun) apply(map, location);
  has_begun = false;
}

void Repeater::apply(Map* map, double end_location) {
  int count = static_cast<int>(floor((end_location - begin_location) / interval)) + 1;
  for (int i = 0; i <= count; i++) {
    auto structToPut = structures[i % structures.size()];
    if (structToPut == nullptr) continue;
    structToPut->add_instance(track->model_mat_at(begin_location + i * interval, 
      x, y, z, rx, ry, rz, tilt, span), begin_location + i * interval);
  }
}
