#pragma once
#include <vector>
#include <memory>
#include <string>
#include "BveMapLexer.h"
#include "BveMapParser.h"
#include "antlr4-runtime.h"

namespace bmets::parser {

class BveMapAntlr {
public:
  std::unique_ptr<antlr4::ANTLRInputStream> istream;
  std::unique_ptr<BveMapLexer> lexer;
  std::unique_ptr<antlr4::CommonTokenStream> tokens;
  std::unique_ptr<BveMapParser> parser;
  BveMapParser::RootContext *root;

  void load(std::string path, std::string content);
};

}