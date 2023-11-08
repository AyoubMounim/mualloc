
#include "mu_allocator/allocator.h"
#include "allocator_private.h"
#include <assert.h>


/* =========================================== Virtual functions declaration */

static void* allocate(Allocator* const, size_t const);
static void _free(Allocator* const, void*);

static AllocatorVtbl const allocatorVtbl = {
  .init = NULL,
  .deinit = NULL,
  .allocate = allocate,
  .free = _free
};


/* ========================================== Interface functions definition */

void* Allocator_allocate(Allocator* const self, size_t const size){
  return self->vptr->allocate(self, size);
}

void Allocator_free(Allocator* const self, void* _obj){
  return self->vptr->free(self, _obj);
}


/* ============================================ Virtual functions definition */

void* allocate(Allocator* const self, size_t const size){
  assert(0);
}

void _free(Allocator* const self, void* _obj){
  assert(0);
}

