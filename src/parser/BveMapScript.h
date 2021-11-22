#pragma once

#include <stack>
#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "../util/FmtException.h"
#include "BveMapValue.h"

namespace antlr4 {
  class ParserRuleContext;
}

namespace bmets::parser {

class BveMapScript;
class BveMapAntlr;

class BveMapStatement {
 public:
  double location;
  int file_index;
  int line;
  int type;
  std::string elem1, elem2, key1, function;
  std::vector<BveMapValue> params;

  const static int TYPE_INVALID = 0;
  const static int TYPE_EF = 1;
  const static int TYPE_EKF = 3;
  const static int TYPE_EKEF = 7;

  std::string to_string();

  void assert_arg_count(int min, int max) {
    if (params.size() < min || params.size() > max) {
      throw FmtException("Invalid argument count (expecting %d~%d, found %d)",
                         min, max, params.size());
    }
  }

  void assert_type(int id, int type) {
    if (params[id].type != type) {
      throw FmtException(
          "Invalid type for argument #%d (expecting %s, found %s)", (id + 1),
          BveMapValue::type_to_string(type),
          BveMapValue::type_to_string(params[id].type));
    }
  }

  bool arg_not_null(int id) {
    return params.size() > id && params[id].type > BveMapValue::TYPE_NULL;
  }

  friend bool operator<(const BveMapStatement &a, const BveMapStatement &b);
};

class BveMapFunction {
 public:
  typedef BveMapValue (*BveMapFunctionPtr)(BveMapScript *script, std::vector<BveMapValue>);

  int arg_count;

  // For built-in functions
  BveMapFunctionPtr func_ptr;

  // For user-defined functions
  std::string name;
  std::vector<std::string> argNames;
  int script_file_index;
  antlr4::ParserRuleContext *antlr_ctx;

  BveMapFunction(BveMapFunctionPtr ptr, int count)
      : arg_count(count), func_ptr(ptr) {}

  BveMapFunction(std::string name, antlr4::ParserRuleContext *ptr, std::vector<std::string> argNames, int file_index)
      : name(name), argNames(argNames), antlr_ctx(ptr), script_file_index(file_index) {
        arg_count = argNames.size();
        func_ptr = nullptr;
      }
  
  // TODO: Is there a better way? Script - File index
  BveMapValue call(BveMapScript *script, std::vector<BveMapValue> args);
};

class ScriptStackFrame {
 public:
  BveMapScript* script;
  ScriptStackFrame* parent;
  int file_index;
  int current_line = -1;
  std::unordered_map<std::string, BveMapValue> variables;
};

class BveMapScript {
 public:
  std::vector<BveMapStatement> statements;
  std::vector<std::string> source_files;
  std::vector<BveMapAntlr*> ast_caches;

  BveMapScript();

  // Recursively loads a file and the files it includes.
  // Does not perform sorting, call sort_statements after all files you want are
  // loaded.
  void load(std::string path);

  // Sort the statements according to their track location.
  void sort_and_cleanup();

  // Internal: Pushes a new stack frame to the top
  ScriptStackFrame* create_stack_frame(int file_index);

  std::string to_string();

  double current_location = 0.0;
  std::stack<ScriptStackFrame> stack;
  std::unordered_map<std::string, BveMapValue> variables;
  std::unordered_map<std::string, BveMapFunction> functions;
};
}  // namespace bmets::parser