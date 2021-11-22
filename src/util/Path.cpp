#include "Path.h"
#include <filesystem>

#ifdef _WIN32
#include "WideStr.h"

std::string path_case_sensitive(std::string original) {
  return original;
}

std::string path_to_abs(std::string relative, std::string baseFile) {
  std::filesystem::path currentDir = std::filesystem::path(Utf8ToWideStr(baseFile)).parent_path();
  if (!currentDir.is_absolute())
    currentDir = std::filesystem::canonical(std::filesystem::current_path()/currentDir);
  std::filesystem::path requestedPath(Utf8ToWideStr(relative));
  if (requestedPath.is_absolute()) {
    return WideStrToUtf8(requestedPath.wstring());
  } else {
    return WideStrToUtf8(std::filesystem::canonical(currentDir/requestedPath).wstring());
  }
}

#else
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include "FmtException.h"

static void replace_delimiter(std::string &path) {
  for (int i = 0; i < path.size(); ++i) {
    if (path[i] == '\\') path[i] = '/';
  }
}

std::string path_case_sensitive(std::string original) {
  replace_delimiter(original);
  std::filesystem::path path(original);
  if (std::filesystem::exists(path)) return original;
  while (path.has_parent_path() && !std::filesystem::exists(path)) {
    path = path.parent_path();
  }
  if (!std::filesystem::exists(path)) {
    throw FmtException("Unable to find existing path root: %s, last tried %s", original.c_str(), path.string().c_str());
  }

  std::vector<std::string> pathParts;
  boost::split(pathParts, original.substr(path.string().size()), boost::is_any_of("/"), boost::token_compress_on);
  int pathPartCount = pathParts.size();
  for (int i = (pathParts[0].empty() ? 1 : 0); i < pathPartCount; ++i) {
    std::string currentPart = boost::algorithm::to_lower_copy(pathParts[i]);
    bool found = false;
    for (auto const& subItem : std::filesystem::directory_iterator(path)) {
      if (i == pathPartCount - 1) {
        if (subItem.is_directory()) continue;
      } else {
        if (!subItem.is_directory()) continue;
      }
      std::string subItemName = subItem.path().filename().string();
      boost::to_lower(subItemName);
      if (subItemName == currentPart) {
        found = true;
        path = subItem.path();
      }
    }
    if (!found) {
      throw FmtException("File cannot be found: %s, last tried %s", original.c_str(), path.string().c_str());
    }
  }
  return path.string();
}

std::string path_to_abs(std::string relative, std::string baseFile) {
  replace_delimiter(relative);
  replace_delimiter(baseFile);
  std::filesystem::path currentDir = std::filesystem::path(baseFile).parent_path();
  if (!currentDir.is_absolute())
    currentDir = std::filesystem::weakly_canonical(std::filesystem::current_path()/currentDir);
  std::filesystem::path requestedPath(relative);
  if (requestedPath.is_absolute()) {
    return path_case_sensitive(requestedPath.string());
  } else {
    return path_case_sensitive(
      std::filesystem::weakly_canonical(currentDir/requestedPath).string()
    );
  }
}
#endif