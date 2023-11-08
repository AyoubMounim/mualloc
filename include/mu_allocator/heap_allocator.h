
#pragma once


typedef struct HeapAllocator HeapAllocator;

typedef HeapAllocator TheHeapAllocator;


/* ========================================= Interface functions declaration */

TheHeapAllocator const* TheHeapAllocator_getInstance(void);
TheHeapAllocator const* TheHeapAllocator_initInstance(void);

