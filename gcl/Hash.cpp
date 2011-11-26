#include "gcl/Hash.h"
#include <cstring>
#include <stdint.h>
#include "md5.h"

#include "gcl/Assert.h"

using namespace GCL;

uint32_t Hash::DJB(const char* str, size_t len)
{
  uint32_t hash = 5381;
  if (len == 0)
    len = strlen(str);
  for(size_t i = 0; i < len; str++, i++)
    {
      hash = ((hash << 5) + hash) + (*str);
    }

  return hash;

}

Hash::MD5Hash Hash::MD5(const char* str, size_t len)
{
  if (len == 0)
    len = strlen(str);

  md5_state_s state;
  md5_init(&state);
  md5_append(&state, (const uint8_t*)str, len);

  MD5Hash hash;
  md5_finish(&state, hash.digest);
  return hash;
}


