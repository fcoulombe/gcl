#pragma once

#include <cstddef>
#include <stdint.h>

namespace GCL
{
  class Hash
  {
  public:
    static uint32_t DJB(const char* str, size_t len=0);

    struct MD5Hash
    {
      uint8_t digest[16];
    };
    static MD5Hash MD5(const char* str, size_t len=0);
  };
}
