/**
 * @file myfree.c
 * @author Paul
 * @version 1.0
 *
 * This file contains the myfree function which free a block in our 
 * shared memory zone.
 *
 */

#include "myfree.h"


int myfree(void *p){
    /** we check if the pointer allocated by mymalloc */
    if(((void*)sharingSpaceMemory <= p)&&(p<=(void*)(sharingSpaceMemory + allMemory))){
        struct memoryBlock* curr = p;
        --curr;
        // printf("adresse du block à libérer : %p, taille : %d\n", curr, curr->size);
        if(curr->free){
            return -1;
        }
        curr->free = 1;
        int blockSize = curr->size;
        myrealloc();
        return blockSize;
    }
    else {
        puts("Please provide a valid pointer allocated");
        return -1;
    }
}

void myrealloc(){
    struct memoryBlock *curr;
    curr = bl;
    while((curr->next) != NULL){
        /** if there are 2 successiv block to free */
        if((curr->next->next) != NULL){
            if((curr->free) && (curr->next->free)){
                /** Current block includes the size of the next block + this meta data */
                curr->size += (curr->next->size) + sizeof(struct memoryBlock);
                curr->next = curr->next->next;
                bt->indexMax = bt->indexMax - 1;
            }
        }
        else{
            /** If the both last block are free, we merge them */
            if((curr->free) && (curr->next->free)){
                curr->size += (curr->next->size) + sizeof(struct memoryBlock);
                curr->next = NULL;
                bt->indexMax = bt->indexMax - 1;
                break;
            }
        }
        curr = curr->next;
    }

}

