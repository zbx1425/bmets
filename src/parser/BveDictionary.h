#pragma once
#include <unordered_map>
#include <string>
#include <vector>

namespace bmets::parser {

  class BveDictionary {
  public:
    std::unordered_map<std::string, std::vector<std::string>> dict;

    void load(std::string path);
    std::string to_string();
    std::string dict_file_path;

    void to_rel_path(int col);
  };
}