
#pragma once

#include <stddef.h>


typedef struct Allocator Allocator;


/* ========================================= Interface functions declaration */

void* Allocator_allocate(Allocator* const self, size_t const size);
void Allocator_free(Allocator* const self, void* _obj);

