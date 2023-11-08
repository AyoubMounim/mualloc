
#pragma once

#include "mu_allocator/allocator.h"
#include <stddef.h>


typedef struct {
  void* (*init)(void* const _self);
  void (*deinit)(void* _self);
  void* (*allocate)(Allocator* const, size_t const);
  void (*free)(Allocator* const, void*);
} AllocatorVtbl;

struct Allocator {
  AllocatorVtbl const* vptr;
};

