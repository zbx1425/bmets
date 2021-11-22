#include "BveMapAntlr.h"
#include "../game/Manager.h"

using namespace bmets::parser;

class AntlrErrorListener : public antlr4::BaseErrorListener {
public:
  std::string path;
  AntlrErrorListener(std::string path) : path(path) {}

  virtual void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line, size_t charPositionInLine,
                           const std::string &msg, std::exception_ptr e) override {
    bmets::game::loader_warn(msg, path, line+1);
  }
};

void BveMapAntlr::load(std::string path, std::string content) {
  istream = std::make_unique<antlr4::ANTLRInputStream>(content);

  AntlrErrorListener listener(path);
  antlr4::DiagnosticErrorListener diagnosticListener;

  lexer = std::make_unique<BveMapLexer>(istream.get());
  lexer->removeErrorListeners();
  lexer->addErrorListener(&listener);
  lexer->addErrorListener(&diagnosticListener);
  tokens = std::make_unique<antlr4::CommonTokenStream>(lexer.get());

  parser = std::make_unique<BveMapParser>(tokens.get());
  parser->removeErrorListeners();
  parser->addErrorListener(&listener);
  parser->addErrorListener(&diagnosticListener);
  root = parser->root();

  if (lexer->getNumberOfSyntaxErrors() > 0 || parser->getNumberOfSyntaxErrors() > 0) {
    throw FmtException("The map file has syntax errors.");
  }

  lexer->removeErrorListeners();
  parser->removeErrorListeners();
}