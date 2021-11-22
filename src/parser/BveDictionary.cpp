#include "BveDictionary.h"
#include <sstream>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include "../util/Path.h"
#include "BveDataFile.h"
#include "../game/Manager.h"

#include <iostream>

using namespace bmets::parser;

void BveDictionary::load(std::string path) {
  dict_file_path = path;

  BveDataFile file;
  file.load(path);
  std::stringstream ss(file.content);
  std::string line;
  std::vector<std::string> tokens;
  while (std::getline(ss, line)) {
    boost::algorithm::trim(line);
    if (line.size() == 0 || line[0] == '#') continue;
    boost::algorithm::split(tokens, line, boost::is_any_of(","));
    for (std::string &token : tokens) {
      boost::trim(token);
    }
    std::string key = boost::algorithm::to_lower_copy(tokens.front());
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());
    dict[key] = args;
  }
}

std::string BveDictionary::to_string() {
  std::stringstream ss;
  for (auto &pair : dict) {
    ss<<pair.first;
    for (auto &arg : pair.second) {
      ss<<','<<arg;
    }
    ss<<std::endl;
  }
  return ss.str();
}

void BveDictionary::to_rel_path(int col) {
  for (auto it = dict.begin(); it != dict.end(); ) {
    auto pair = *it;
    if (pair.second.size() > col) {
      if (pair.second[col].empty()) {
        ++it;
        continue;
      }
      try {
        it->second[col] = path_to_abs(pair.second[col], dict_file_path);
        ++it;
      } catch (std::exception &ex) {
        bmets::game::loader_warn("Cannot locate file '" + pair.second[col] + "' : " + ex.what(), dict_file_path, -1);
        it = dict.erase(it);
      }
    }
  }
}