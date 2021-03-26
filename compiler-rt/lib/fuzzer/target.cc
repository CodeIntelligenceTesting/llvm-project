#include <cstdint>
#include <cstddef>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < 10)
    return 0;
  if (Data[0] == 5 && Data[9] == 7) {
    exit(1);
  }
  return 0;
}
