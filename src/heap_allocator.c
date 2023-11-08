
#include "mu_allocator/heap_allocator.h"
#include "mu_allocator/allocator.h"
#include "allocator_private.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>


struct HeapAllocator {
  Allocator super;
};

static TheHeapAllocator* singletonInstance = NULL;


/* =========================================== Virtual functions declaration */

static void* init(void* const);
static void deinit(void*);
static void* allocate(Allocator* const, size_t const);
static void _free(Allocator* const, void*);

static AllocatorVtbl const allocatorVtbl = {
  .init = init,
  .deinit = deinit,
  .allocate = allocate,
  .free = _free
};


/* ========================================== Interface functions definition */

TheHeapAllocator const* TheHeapAllocator_initInstance(void){
  static uint8_t sigletonStorage[sizeof(HeapAllocator)];
  singletonInstance = (TheHeapAllocator*) sigletonStorage;
  init(singletonInstance);
  return singletonInstance;
}

TheHeapAllocator const* TheHeapAllocator_getInstance(void){
  if (singletonInstance){
    return singletonInstance;
  }
  TheHeapAllocator_initInstance();
  return singletonInstance;
}

/* ============================================ Virtual functions definition */

void* init(void* const _self){
  HeapAllocator* self = _self;
  assert(&(self->super));
  self->super.vptr = &allocatorVtbl;
  return self;
}

void deinit(void* _self){
  return;
}

void* allocate(Allocator* const self, size_t const size){
  return calloc(1, size);
}

void _free(Allocator* const self, void* _obj){
  free(_obj);
  return;
}

