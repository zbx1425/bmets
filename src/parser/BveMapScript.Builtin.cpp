#include "BveMapScript.h"
#include <cmath>
#include <ctime>
#include <random>
#include <sstream>
#include "../game/Manager.h"

using namespace bmets::parser;

static FmtException exception_value_type(std::string place, std::string expected, int type) {
  return FmtException("Type mismatch at '%s' where (%s) is expected but (%s) is encountered", 
    place.c_str(), expected.c_str(), BveMapValue::type_to_string(type));
}

static BveMapValue builtin_abs(BveMapScript *script, std::vector<BveMapValue> params) {
  switch (params[0].type) {
  case BveMapValue::TYPE_INT: return BveMapValue(std::abs(params[0].value_int));
  case BveMapValue::TYPE_DOUBLE: return BveMapValue(std::abs(params[0].value_double));
  case BveMapValue::TYPE_NULL: return BveMapValue(BveMapValue::TYPE_NULL);
  }
  throw exception_value_type("abs", "number", params[0].type);
}

static BveMapValue builtin_ceil(BveMapScript *script, std::vector<BveMapValue> params) {
  switch (params[0].type) {
  case BveMapValue::TYPE_INT: return params[0];
  case BveMapValue::TYPE_DOUBLE: return static_cast<int>(std::ceil(params[0].value_double));
  case BveMapValue::TYPE_NULL: return BveMapValue(BveMapValue::TYPE_NULL);
  }
  throw exception_value_type("ceil", "number", params[0].type);
}

static BveMapValue builtin_floor(BveMapScript *script, std::vector<BveMapValue> params) {
  switch (params[0].type) {
  case BveMapValue::TYPE_INT: return params[0];
  case BveMapValue::TYPE_DOUBLE: return static_cast<int>(std::floor(params[0].value_double));
  case BveMapValue::TYPE_NULL: return BveMapValue(BveMapValue::TYPE_NULL);
  }
  throw exception_value_type("floor", "number", params[0].type);
}

static BveMapValue builtin_atan2(BveMapScript *script, std::vector<BveMapValue> params) {
  return std::atan2(params[0].to_double("atan2 (x)"), params[1].to_double("atan2 (y)"));
}

static BveMapValue builtin_cos(BveMapScript *script, std::vector<BveMapValue> params) {
  return std::cos(params[0].to_double("cos"));
}

static BveMapValue builtin_exp(BveMapScript *script, std::vector<BveMapValue> params) {
  return std::exp(params[0].to_double("exp"));
}

static BveMapValue builtin_log(BveMapScript *script, std::vector<BveMapValue> params) {
  return std::log(params[0].to_double("log"));
}

static BveMapValue builtin_pow(BveMapScript *script, std::vector<BveMapValue> params) {
  return std::pow(params[0].to_double("pow (base)"), params[0].to_double("pow (exponent)"));
}

static BveMapValue builtin_sin(BveMapScript *script, std::vector<BveMapValue> params) {
  return std::sin(params[0].to_double("sin"));
}

static BveMapValue builtin_sqrt(BveMapScript *script, std::vector<BveMapValue> params) {
  return std::sqrt(params[0].to_double("sqrt"));
}

static std::default_random_engine rand_engine(std::time(0));
static BveMapValue builtin_rand(BveMapScript *script, std::vector<BveMapValue> params) {
  if (params.size() > 1) throw FmtException("Invalid argument count, 0/1 expected but %d found", params.size());
  if (params.size() == 0) {
    return std::uniform_real_distribution()(rand_engine);
  } else {
    return std::uniform_int_distribution(0, params[0].to_int())(rand_engine);
  }
}

static const char* DEBUG_FILE_TAG = "Debug Print";

static BveMapValue builtin_print(BveMapScript *script, std::vector<BveMapValue> params) {
  std::stringstream ss;
  for (int i = 0; i < params.size(); ++i) {
    if (i > 0) ss << '\n';
    ss<<params[i].to_string();
  }
  bmets::game::loader_warn(ss.str(), DEBUG_FILE_TAG, -1);
  return BveMapValue(BveMapValue::TYPE_NULL);
}

static BveMapValue builtin_var_dump(BveMapScript *script, std::vector<BveMapValue> params) {
  bmets::game::loader_warn(params[0].to_string() + " (" + params[0].type_to_string() + ")"
    , DEBUG_FILE_TAG, -1);
  return BveMapValue(BveMapValue::TYPE_NULL);
}

static BveMapValue builtin_var_dump_all(BveMapScript *script, std::vector<BveMapValue> params) {
  std::stringstream ss;
  for (auto pair : script->variables) {
    ss<<pair.first<<": "<<pair.second.to_string()<<" ("<<pair.second.type_to_string()<<")\n";
  }
  for (auto pair : script->stack.top().variables) {
    ss<<pair.first<<": "<<pair.second.to_string()<<" ("<<pair.second.type_to_string()<<")\n";
  }
  bmets::game::loader_warn(ss.str(), DEBUG_FILE_TAG, -1);
  return BveMapValue(BveMapValue::TYPE_NULL);
}

static BveMapValue builtin_stack_dump(BveMapScript *script, std::vector<BveMapValue> params) {
  std::stringstream ss;
  ScriptStackFrame *frame = &script->stack.top();
  while (frame != nullptr) {
    ss<<"At L"<<frame->current_line<<" of "<<script->source_files[frame->file_index]<<"\n";
    for (auto pair : frame->variables) {
      ss<<"  "<<pair.first<<": "<<pair.second.to_string()<<" ("<<pair.second.type_to_string()<<")\n";
    }
    frame = frame->parent;
  }
  bmets::game::loader_warn(ss.str(), DEBUG_FILE_TAG, -1);
  return BveMapValue(BveMapValue::TYPE_NULL);
}

BveMapScript::BveMapScript() {
  functions.emplace("abs", BveMapFunction(builtin_abs, 1));
  functions.emplace("atan2", BveMapFunction(builtin_atan2, 2));
  functions.emplace("ceil", BveMapFunction(builtin_ceil, 1));
  functions.emplace("cos", BveMapFunction(builtin_cos, 1));
  functions.emplace("exp", BveMapFunction(builtin_exp, 1));
  functions.emplace("floor", BveMapFunction(builtin_floor, 1));
  functions.emplace("log", BveMapFunction(builtin_log, 1));
  functions.emplace("pow", BveMapFunction(builtin_pow, 1));
  functions.emplace("sin", BveMapFunction(builtin_sin, 1));
  functions.emplace("sqrt", BveMapFunction(builtin_sqrt, 1));
  functions.emplace("rand", BveMapFunction(builtin_rand, -1));
  functions.emplace("print", BveMapFunction(builtin_print, -1));
  functions.emplace("var_dump", BveMapFunction(builtin_var_dump, 1));
  functions.emplace("var_dump_all", BveMapFunction(builtin_var_dump_all, 0));
  functions.emplace("print_stack_trace", BveMapFunction(builtin_stack_dump, 0));
}