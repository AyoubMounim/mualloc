
#include "mu_allocator/stack_allocator.h"
#include "stack_allocator_private.h"
#include "mu_allocator/allocator.h"
#include "allocator_private.h"
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>


static TheStackAllocator* singletonInstance = NULL;


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

TheStackAllocator* TheStackAllocator_initInstance(void){
  static uint8_t sigletonStorage[sizeof(StackAllocator)];
  singletonInstance = (TheStackAllocator*) sigletonStorage;
  init(singletonInstance);
  return singletonInstance;
}

TheStackAllocator* TheStackAllocator_getInstance(void){
  if (singletonInstance){
    return singletonInstance;
  }
  TheStackAllocator_initInstance();
  return singletonInstance;
}

/* ============================================ Virtual functions definition */

void* init(void* const _self){
  StackAllocator* self = _self;
  assert(&(self->super));
  self->super.vptr = &allocatorVtbl;
  return self;
}

void deinit(void* _self){
  return;
}

void* allocate(Allocator* const self, size_t const size){
  return alloca(size);
}

void _free(Allocator* const self, void* _obj){
  return;
}

