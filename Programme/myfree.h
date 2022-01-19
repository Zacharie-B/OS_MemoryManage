/**
 * @file myfree.h
 * @author Zacharie
 * 
 * Declare the prototypes of function myfree and myrealloc use in the @see myfree.c
 * in order to deallocated the memory.
 */

#ifndef __myfree_h
#define __myfree_h

#include "initializer.h"

/**
 * @brief Free a memoryblock in the blocklist.
 * 
 * @param p zone of memory who are going to be deallocated
 * @return int -1 if an error occurs the size of the space deallocated if no problem occurs 
 */
int myfree(void *p);

/**
 * @brief Merge memory blocks if we have deallocated 2 memory block odds by odds.
 * 
 */
void myrealloc();

#endif