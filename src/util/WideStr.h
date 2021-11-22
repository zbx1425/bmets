#pragma once

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <string>

#pragma warning (disable:4267)

inline static std::wstring Utf8ToWideStr(std::string str) {
  std::wstring ret;
  int len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0);
  if (len > 0) {
    ret.resize(len);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len);
  }
  return ret;
}

inline static std::string WideStrToUtf8(std::wstring str) {
  std::string ret;
  int len = WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), NULL, 0, NULL, NULL);
  if (len > 0) {
    ret.resize(len);
    WideCharToMultiByte(CP_UTF8, 0, str.c_str(), str.length(), &ret[0], len, NULL, NULL);
  }
  return ret;
}
#endif