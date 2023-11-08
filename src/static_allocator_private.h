
#include "mu_allocator/static_allocator.h"
#include "allocator_private.h"
#include <stdint.h>

#define ALLOCATION_STORAGE_SIZE 1000


struct StaticAllocator {
  Allocator super;
  uintptr_t storageStart;
  uint32_t allocatedSpaceCounter;
};

