#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/split.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "../util/Iconvpp.h"
#include "../util/WideStr.h"
#include "../util/Path.h"
#include "BveDataFile.h"
#include "../game/Manager.h"
#include "../util/FmtException.h"

using namespace bmets::parser;

#include <fstream>
#include <sstream>
#include <cerrno>

static std::string get_file_contents(std::string filename) {
#ifdef _WIN32
  std::ifstream in(Utf8ToWideStr(filename).c_str(), std::ios::in | std::ios::binary);
#else
  std::ifstream in(filename, std::ios::in | std::ios::binary);
#endif
  if (in)
  {
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw FmtException("IO error when reading file: %d", errno);
}

void BveDataFile::load(std::string path) {
  std::string rawContent = get_file_contents(path_case_sensitive(path));
  std::istringstream rawContentStream(rawContent);

  { // Skip UTF-8 BOM.
    int a = rawContentStream.get(), b = rawContentStream.get(), c = rawContentStream.get();
    if (a != 0xEF || b != 0xBB || c != 0xBF) rawContentStream.seekg(0);
  }

  std::getline(rawContentStream, header);
  boost::trim(header);
  boost::to_lower(header);
  if (!boost::starts_with(header, "bvets ")) {
    throw FmtException("This is not a BveTs data file.");
  }

  std::vector<std::string> encodingParts(2);
  if (header.find(':') != std::string::npos) {
    boost::split(encodingParts, header, boost::is_any_of(":"));
    boost::trim(encodingParts[0]);
    boost::trim(encodingParts[1]);
  } else {
    encodingParts[0] = header;
    encodingParts[1] = "utf-8";
  }
  encoding = boost::algorithm::to_lower_copy(encodingParts[1]);
  size_t lastSpacePos = encodingParts[0].find_last_of(' ');
  version = encodingParts[0].substr(lastSpacePos + 1);
  type = encodingParts[0].substr(6, lastSpacePos - 6);
  
  std::streampos contentBeginPos = rawContentStream.tellg();
  if (encoding == "utf-8" || encoding == "utf8") {
    content = rawContent.substr(contentBeginPos);
  } else {
    iconvpp::converter conv("utf-8", encoding, false, 4096);
    conv.convert(&rawContent[contentBeginPos], rawContent.size() - contentBeginPos, content);
  }
}