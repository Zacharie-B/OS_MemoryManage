/**
 * @file allocate.h
 * @author Zacharie
 * 
 * Declare the prototypes of function myalloc and splitAllcate use in the @see myallocate.c 
 * in order to allocated the memory.
 */

#ifndef __allocate_h
#define __allocate_h

#include "initializer.h"

/**
 * @brief Allocate a memoryblock in the blocklist
 * 
 * @param nBytes number of bytes to allocates
 * @return void* address of beginning chain allocate
 */
void* mymalloc(int nBytes);

/**
 * @brief Allocate a memory block with the creation of a new memory
 * block who do exactly the requested size.
 * 
 * @param currentBlock address of current block
 * @param size of new block
 */
void splitAllocate(struct memoryBlock *currentBlock, size_t size);

#endif