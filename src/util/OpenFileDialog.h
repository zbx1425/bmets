#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>
#include "WideStr.h"

inline static std::string OpenFileDialog() {
  OPENFILENAMEW ofn;
  WCHAR szFile[MAX_PATH];
  ZeroMemory(&ofn, sizeof(ofn));
  ofn.lStructSize = sizeof(ofn);
  ofn.lpstrFile = szFile;
  ofn.lpstrFile[0] = '\0';
  ofn.hwndOwner = NULL;
  ofn.nMaxFile = sizeof(szFile);
  ofn.lpstrFilter = NULL;
  ofn.nFilterIndex = 1;
  ofn.lpstrTitle = TEXT("Select file");
  ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
  if (GetOpenFileNameW(&ofn)) {
    return WideStrToUtf8(std::wstring(ofn.lpstrFile));
  } else {
    return "";
  }
}
#else
#include <boost/algorithm/string/trim.hpp>
inline static std::string OpenFileDialog() {
  char buf[1024];
  FILE *f = popen("zenity --file-selection", "r");
  fgets(buf, 1024, f);
  if (pclose(f) < 0) return "";
  return boost::algorithm::trim_copy(std::string(buf));
}
#endif