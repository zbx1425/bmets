#pragma once
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

#include "../math/Track.h"
// Forward Declarations.
namespace bmets::render { class ModelList; }
namespace bmets::parser { class BveMapScript; }

namespace bmets::game {

  class Map;

  class Repeater {
  public:
    double x, y, z, rx, ry, rz, span, interval, begin_location;
    int tilt;
    bool has_begun;
    bmets::math::Followable* track;
    std::vector<bmets::render::ModelList*> structures;
    void begin(Map* map, double location, bmets::math::Followable* track, 
      double x, double y, double z, double rx, double ry, double rz,
      int tilt, double span, double interval, std::vector<bmets::render::ModelList*> structures);
    void end(Map* map, double location);
  private:
    void apply(Map* map, double end_location);
  };

  class Map {
  public:
    std::unordered_map<std::string, std::unique_ptr<bmets::math::ChildTrack>> tracks;
    bmets::math::MainTrack track_main;
    std::unordered_map<std::string, Repeater> repeaters;
    void parse_script_data(bmets::parser::BveMapScript &data, int loadFlag);
    void clear();

  };
}