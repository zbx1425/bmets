/*
Copyright (c) 2011, Yuya Unno
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Yuya Unno nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <errno.h>
#include <iconv.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "FmtException.h"

namespace iconvpp {

class converter {
 public:
  converter(const std::string& out_encode,
            const std::string& in_encode,
            bool ignore_error = false,
            size_t buf_size = 1024)
      : ignore_error_(ignore_error),
        buf_size_(buf_size) {
    if (buf_size == 0) {
      throw FmtException("Buffer size must be greater than zero");
    }

    iconv_t conv = ::iconv_open(out_encode.c_str(), in_encode.c_str());
    if (conv == (iconv_t)-1) {
      if (errno == EINVAL)
        throw FmtException("Unsupported charset: %s", in_encode.c_str());
      else
        throw FmtException("General ICONV error: %d", errno);
    }
    iconv_ = conv;
  }

  ~converter() {
    iconv_close(iconv_);
  }

  void convert(const char* src_ptr, size_t src_size, std::string& output) const {
    std::vector<char> buf(buf_size_);
    std::string dst;
    while (0 < src_size) {
      char* dst_ptr = &buf[0];
      size_t dst_size = buf.size();
#ifdef _WIN32
      size_t res = ::iconv(iconv_, (const char**) &src_ptr, &src_size, &dst_ptr, &dst_size);
#else
      size_t res = ::iconv(iconv_, (char**) &src_ptr, &src_size, &dst_ptr, &dst_size);
#endif
      if (res == (size_t)-1) {
        if (errno == E2BIG)  {
          // ignore this error
        } else if (ignore_error_) {
          // skip character
          ++src_ptr;
          --src_size;
        } else {
          check_convert_error();
        }
      }
      dst.append(&buf[0], buf.size() - dst_size);
    }
    dst.swap(output);
  }

  inline void convert(const std::string& input, std::string& output) const {
    convert(&input[0], input.size(), output);
  }

 private:
  void check_convert_error() const {
    switch (errno) {
      case EILSEQ:
      case EINVAL:
        throw FmtException("Invalid byte sequence in file. Is the charset correct?");
      default:
        throw FmtException("General ICONV error: %d", errno);
    }
  }

  iconv_t iconv_;
  bool ignore_error_;
  const size_t buf_size_;
};

}  // namespace iconvpp