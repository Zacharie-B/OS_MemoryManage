/**
 * @file initializer.h
 * @author Zacharie and Paul
 * 
 * Declare the prototypes of function @see main.c and get all library in order to create
 * the features for our programm.
 */
#ifndef __initializer_h
#define __initializer_h

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/** @def Number of turn given to programm in order to allocate and de-allocate; */
#define TURN_NUMBER 50

/** we creates a table of char (byte) which will be our shared memory */
char *sharingSpaceMemory;

/** Totally size allocate at the beginning of programm */
size_t allMemory;

/** 
 * @struct memoryBlock initializer.h
 * This struct will use for to manage our memory space with memory blocks.
 */
typedef struct memoryBlock{
    /** size of block of memory*/
    size_t size;
    /** if the block memory is free, free = 1, else free = 0 */
    int free;
    /** pointer on the next block */
    struct memoryBlock *next;
    }*BlockListe;
BlockListe bl;

/**
 * @struct BlockTable initializer.h
 * This struct list memory blocks.
 */
typedef struct{
    /** Table of memory block used during the test programm*/
    struct memoryBlock **block;

    /** Index max of table */
    int indexMax;
} BlockTable;

BlockTable *bt;

/**
 * Initialize the shared memory zone, in order to create our work zone, 
 * and initialize the manager of memory Block.
 * @param nBytes size of zmemory one to allocate
 * @return int the number of bytes effectively allocated on success, 0 on failure
 */
int initMemory(int nBytes);

/**
 * @brief Allocate the memory for one block given in parameter.
 * 
 * @param n size of one block memory
 * @param tab address of block to allocate
 * @return int size in bytes from block effectively allocate
 */
int allocTabP(int n, char **tab);

/**
 * Free the memory initially allocated with the "initMemory()" function.
 * @return int the number of bytes effectively free on success, -1 on failure
 */
int freeMemory();

/**
 * @brief Free one block of memory.
 * 
 * @param tab address of block to free
 * @return int size of bytes of block effectively free
 */
int libMemTabP(char **tab);


/**
 * @brief Display all elements about the memory block list.
 * 
 */
void displayMemoryAllocate();

#endif