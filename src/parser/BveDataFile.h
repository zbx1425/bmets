#pragma once
#include <string>

namespace bmets::parser {
  
  class BveDataFile {
    public:
      std::string header, type, version, encoding;

      std::string content;

      void load(std::string path);
  };
}