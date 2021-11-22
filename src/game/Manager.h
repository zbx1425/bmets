#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "Timer.h"
#include "Map.h"

#ifdef GLOBAL_VAR_IMPL
  #define EXTERN_OR_DEF
  #define DEF_ARG_LIST(A) (A)
#else
  #define EXTERN_OR_DEF extern
  #define DEF_ARG_LIST(A)
#endif

namespace bmets::game {

  EXTERN_OR_DEF Map map;

  void reset(int loadFlag);
  int load(std::string path, int loadFlag);

  // Load Flags (or Reset Flags)
  const int LOAD_ALL = 0;             // Full loading
  const int LOAD_SKIP_STRUCTURE = 1;  // Don't load structures, use these already loaded last time
  const int LOAD_KEEP_WARN = 2;       // Don't reset the warning list and exception

  const int TIMER_PARSE_ANTLR = 1;
  const int TIMER_PARSE_EXEC = 2;
  const int TIMER_PARSE_APPLY = 5;
  const int TIMER_MODEL = 10;
  const int TIMER_MODEL_INSTANCE = 18;
  const int TIMER_TEXTURE = 20;
  const int TIMER_SIZE = 30;

  struct LoaderWarning {
    std::string message;
    int line;
  };

  EXTERN_OR_DEF std::unordered_map<std::string, std::vector<LoaderWarning>> loader_warnings;
  EXTERN_OR_DEF LoaderWarning loader_exception;
  EXTERN_OR_DEF void (*loader_progress_callback)(std::string message, int percent);
  EXTERN_OR_DEF Timer timer DEF_ARG_LIST(TIMER_SIZE);

  void loader_warn(std::string message, std::string file, int line);
  void loader_progress(std::string message, int percent);
}
