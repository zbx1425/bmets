#define GLOBAL_VAR_IMPL
#include "Manager.h"
#include "Map.h"
#include "../parser/BveMapScript.h"
#include "../render/Manager.h"

#include <boost/algorithm/string/trim.hpp>
#include <cstdio>

using namespace bmets::game;
using namespace bmets::render;

void bmets::game::reset(int loadFlag) {
  if (!(loadFlag & LOAD_KEEP_WARN)) {
    loader_warnings.clear();
    loader_exception = {};
  }
  bmets::render::reset(loadFlag);
}

int bmets::game::load(std::string path, int loadFlag) {
  try {
    bmets::game::reset(loadFlag);
    timer.clear();

    loader_progress(std::string("Parsing map script ..."), -1);
    bmets::parser::BveMapScript mapScript;
    mapScript.load(path);
    if (mapScript.statements.size() == 0) {
      throw FmtException("The map file failed to parse, or does not contain anything.");
    }
    mapScript.sort_and_cleanup();

    timer.begin(TIMER_PARSE_APPLY);
    map.clear();
    map.parse_script_data(mapScript, loadFlag);

    timer.begin(TIMER_MODEL);
    model_manager.load_all(loadFlag);
    timer.begin(TIMER_TEXTURE);
    texture_manager.load_all(loadFlag);
    timer.begin(TIMER_MODEL_INSTANCE);
    model_manager.opacity_sort();
    model_manager.generate_vaos(0);
    timer.end();

    if (bmets::game::loader_warnings.size() > 0) {
      return 1;
    }
    return 0;
  } catch (std::exception &ex) {
    map.clear();
    bmets::game::loader_exception = { ex.what(), -1 };
    bmets::game::reset(bmets::game::LOAD_KEEP_WARN);
    return -1;
  }
}

void bmets::game::loader_warn(std::string message, std::string file, int line) {
  auto it = loader_warnings.find(file);
  if (it == loader_warnings.end()) {
    loader_warnings[file] = std::vector<LoaderWarning>();
  }
  LoaderWarning warn { boost::algorithm::trim_copy(message), line };
  loader_warnings[file].push_back(warn);
}

void bmets::game::loader_progress(std::string message, int percent) {
  if (loader_progress_callback != nullptr) loader_progress_callback(message, percent);
}
