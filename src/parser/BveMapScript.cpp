#include <sstream>
#include <iostream>

#include "BveMapScript.h"
#include "BveDataFile.h"
#include "BveMapVisitor.h"
#include "BveMapLexer.h"
#include "BveMapParser.h"
#include "BveMapValue.h"
#include "antlr4-runtime.h"

#include "BveMapAntlr.h"

#include "../game/Manager.h"
#include "../util/FmtException.h"

#include <algorithm>

using namespace bmets::parser;
using namespace antlr4;

namespace bmets::parser {

  bool operator< (const BveMapStatement &a, const BveMapStatement &b) {
    // TODO: Is this enough?
    if (a.location == b.location) {
      if (a.file_index == b.file_index) {
        return a.line < b.line;
      } else {
        return a.file_index < b.file_index;
      }
    } else {
      return a.location < b.location;
    }
  }
}

static const int STACK_DEPTH_LIMIT = 1000;

ScriptStackFrame* BveMapScript::create_stack_frame(int file_index) {
  if (stack.size() > STACK_DEPTH_LIMIT) {
    throw FmtException("Stack depth limit of %d exceeded. Check for loop include reference or infinite recursive function calls.", STACK_DEPTH_LIMIT);
  }
  ScriptStackFrame frame {
    this, stack.size() > 0 ? &stack.top() : nullptr, file_index
  };
  stack.push(frame);
  return &stack.top();
}

void BveMapScript::load(std::string path) {
  // TODO: Check for loop reference

  int current_file_index;
  auto srcIt = std::find(source_files.begin(), source_files.end(), path);
  if (srcIt != source_files.end()) {
    current_file_index = srcIt - source_files.begin();
  } else {
    current_file_index = source_files.size();
    source_files.emplace_back(path);
    ast_caches.emplace_back(nullptr);
  }

  ScriptStackFrame *frame = create_stack_frame(current_file_index);
  BveDataFile file;
  file.load(path);
  if (file.type != "map") {
    // TODO: Check Version
    throw FmtException("This is not a map file: %s", file.header.c_str());
  }
  
  bmets::game::timer.begin(bmets::game::TIMER_PARSE_ANTLR);
  if (ast_caches[current_file_index] == nullptr) {
    ast_caches[current_file_index] = new BveMapAntlr;
    ast_caches[current_file_index]->load(path, file.content);
  }
  tree::ParseTree *tree = ast_caches[current_file_index]->root;

  bmets::game::timer.begin(bmets::game::TIMER_PARSE_EXEC);
  BveMapVisitor visitor(frame);
  try {
    visitor.visit(tree);
  } catch (std::exception &ex) {
    bmets::game::loader_warn(ex.what(), source_files[frame->file_index], frame->current_line);
    throw FmtException("A scripting error occured when loading the map file. Details are included in other messages.");
  }

  stack.pop();
}

void BveMapScript::sort_and_cleanup() {
  std::sort(statements.begin(), statements.end());
  for (auto astCache : ast_caches) {
    delete astCache;
  }
  ast_caches.clear();
}

std::string BveMapStatement::to_string() {
  std::stringstream ss;
  ss<<location<<"; "<<elem1;
  if (type == BveMapStatement::TYPE_EKF || type == BveMapStatement::TYPE_EKEF) {
    ss<<'['<<key1<<']';
  }
  if (type == BveMapStatement::TYPE_EKEF) {
    ss<<'.'<<elem2;
  }
  ss<<'.'<<function<<'(';
  for (int i = 0; i < params.size(); i++) {
    if (i > 0) ss<<',';
    ss<<params[i].to_string();
    
  }
  ss<<");";
  return ss.str();
}

std::string BveMapScript::to_string() {
  std::stringstream ss;
  for (auto stmt : this->statements) {
    ss<<stmt.to_string()<<std::endl;
  }
  return ss.str();
}

BveMapValue BveMapFunction::call(BveMapScript *script, std::vector<BveMapValue> args) {
  if (arg_count >= 0 && args.size() != arg_count)
    throw FmtException("Invalid argument count, %d expected but %d found",
                        arg_count, args.size());
  if (func_ptr) {
    return func_ptr(script, args);
  } else {
    ScriptStackFrame *frame = script->create_stack_frame(script_file_index);
    for (int i = 0; i < arg_count; ++i) {
      std::string argName = argNames[i];
      if (argName[0] == '$') {
        script->variables[argName] = args[i];
      } else {
        frame->variables[argName] = args[i];
      }
    }
    BveMapVisitor visitor(frame);
    visitor.visit(antlr_ctx);
    BveMapValue result;
    auto entry = frame->variables.find("%" + name);
    if (entry == frame->variables.end()) {
      result = BveMapValue();
    } else {
      result = entry->second;
    }
    script->stack.pop();
    return result;
  }
}