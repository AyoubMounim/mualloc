

#pragma once


typedef struct StackAllocator StackAllocator;

typedef StackAllocator TheStackAllocator;


/* ========================================= Interface functions declaration */

TheStackAllocator* TheStackAllocator_initInstance(void);
TheStackAllocator* TheStackAllocator_getInstance(void);

