
#pragma once


typedef struct StaticAllocator StaticAllocator;

typedef StaticAllocator TheStaticAllocator;


/* ========================================= Interface functions declaration */

TheStaticAllocator* TheStaticAllocator_initInstance(void);
TheStaticAllocator* TheStaticAllocator_getInstance(void);

