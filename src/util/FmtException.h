#pragma once
#include <memory>

class FmtException : public std::exception {
public:
  std::unique_ptr<char[]> msg;

  FmtException(const char* fmt, ...);

  virtual char const* what() const noexcept {
      return msg.get() != nullptr ? msg.get() : "Unknown exception";
  }
};
