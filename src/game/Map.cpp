#include "Map.h"

using namespace bmets::game;

void Map::clear() {
  track_main.clear();
  for (auto &track : tracks) {
    track.second->clear();
  }
  tracks.clear();
}