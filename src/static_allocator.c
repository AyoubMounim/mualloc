
#include "static_allocator_private.h"
#include "allocator_private.h"
#include <assert.h>
#include <stdint.h>


static uint8_t storage[ALLOCATION_STORAGE_SIZE];

static TheStaticAllocator* singletonInstance = NULL;


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


/* ============================================ Virtual functions definition */

void* init(void* const _self){
  StaticAllocator* self = _self;
  assert(&(self->super));
  self->super.vptr = &allocatorVtbl;
  self->storageStart = (uintptr_t) storage;
  self->allocatedSpaceCounter = 0;
  return self;
}

void deinit(void* _self){
  StaticAllocator* self = _self;
  self->storageStart = 0;
  self->allocatedSpaceCounter = 0;
  return;
}

void* allocate(Allocator* const self, size_t const size){
  StaticAllocator* actualSelf = (StaticAllocator*) self;
  uintptr_t allocationAddr = 0;
  if (actualSelf->allocatedSpaceCounter + size <= ALLOCATION_STORAGE_SIZE){
    allocationAddr = actualSelf->storageStart + actualSelf->allocatedSpaceCounter;
    actualSelf->allocatedSpaceCounter += size;
  }
  return (void*) allocationAddr;
}

void _free(Allocator* const self, void* _obj){
  return;
}


/* ========================================== Interface functions definition */

TheStaticAllocator* TheStaticAllocator_initInstance(void){
  static uint8_t singletonStorage[sizeof(StaticAllocator)] = {0};
  if (!singletonInstance){
    singletonInstance = (TheStaticAllocator*) singletonStorage;
    init(singletonInstance);
  }
  return singletonInstance;
}

TheStaticAllocator* TheStaticAllocator_getInstance(void){
  if (!singletonInstance){
    singletonInstance = TheStaticAllocator_initInstance();
  }
  return singletonInstance;
}

