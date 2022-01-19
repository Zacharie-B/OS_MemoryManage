/**
 * @file allocate.c
 * @author Zacharie
 * @version 1.0
 *
 * This file implement functions which do the allocation of memory block in our memory
 * of work. We use the best fit method in order to find the best block for the allocation.
 * 
 */
#include "allocate.h"

void* mymalloc(int nBytes){
    struct memoryBlock *curr, *bestblock;
    size_t bestSizeBlock = allMemory + 10;
    void *result;

    /** creation of a temporary pointer curr */
    curr = bl;
    bestblock = bl;

    while(curr != NULL){
        /** we check if the memory block has the exact size */
        if((curr->size == (nBytes + sizeof(struct memoryBlock)) && (curr->free))){
            bestblock = curr;
            puts("Best memory block found");
            break;
        }
        
        /** we check if the  memory block has the smallest possible size */
        else if((curr->size > (nBytes + sizeof(struct memoryBlock)) && (curr->size < bestSizeBlock) && (curr->free))){
            bestblock = curr;
            bestSizeBlock = curr->size;
            puts("Potential best memory block found");
        }
        if(curr->next == NULL) break;
        curr = curr->next;
    }

    /** we realize the allocation of one block if we are in the best size case */
    if(((bestblock->size) == (nBytes + sizeof(struct memoryBlock))) && (bestblock->free)){
        bestblock->free = 0;
        result = (void*)(++bestblock);
        puts("Best fit of memory block allocated");
        printf("Number of bytes allocate : %d\n", nBytes);
        return result;
    }

    /** we create a new block with the right size thanks to the splitAllocate function */
    else if(((bestblock->size) > (nBytes + sizeof(struct memoryBlock))) && (bestblock->free)){
        splitAllocate(bestblock, nBytes);
        result = (void*)(++bestblock);
        puts("Fit for block allocated with a split");
        printf("Number of bytes allocate : %d\n", nBytes);
        return result;
    }

    else{
        result = 0;
        printf("Insufficient memory : %d bytes too big for our memory\n", nBytes);
        return result;
    }
}

void splitAllocate(struct memoryBlock *currentBlock, size_t size){
    /** We create a new memory block after the current memory block*/
    struct memoryBlock *new = (void*)((void*)currentBlock + size + sizeof(struct memoryBlock));
    new->size = (currentBlock->size) - size - sizeof(struct memoryBlock);
    new->free = 1;
    new->next = currentBlock->next;
    
    currentBlock->size = size;
    currentBlock->free = 0;
    currentBlock->next = new;
}