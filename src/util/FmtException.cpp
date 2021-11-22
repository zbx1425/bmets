#include "FmtException.h"
#include <cstdio>
#include <cstdarg>

FmtException::FmtException(const char* fmt, ...) {
  va_list argptr;
  
  va_start(argptr, fmt);
  int size_s = std::vsnprintf(nullptr, 0, fmt, argptr) + 1;
  va_end(argptr);

  va_start(argptr, fmt);
  if(size_s > 0){
    msg = std::make_unique<char[]>(static_cast<size_t>(size_s));
    std::vsnprintf(msg.get(), static_cast<size_t>(size_s), fmt, argptr);
  } else {
    msg = nullptr;
  }
  va_end(argptr);
}