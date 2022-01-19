#include "initializer.h"

int initMemory(int nBytes){
    int memoryAllocate = allocTabP(nBytes, &sharingSpaceMemory);

    if(sharingSpaceMemory == NULL){
        return 0;
    }

    /** We update the address of blockliste with the address of sharing memory zone */
    bl = (void*)sharingSpaceMemory;
    bl->size = nBytes - sizeof(BlockListe);
    bl->free = 1;
    bl->next = NULL;
    return memoryAllocate;
}


int allocTabP(int n, char **tab){
    *tab = (char*)malloc(n*sizeof(char));
    if(*tab == NULL){
        printf("\n Il y a eu un problème d'allocation mémoire du tableau.");
        return 0;
    }
    return n * sizeof(char);
}


int freeMemory(){
    int memoryToFree = libMemTabP(&sharingSpaceMemory);
    if(sharingSpaceMemory != NULL){
        return -1;
    }
    return memoryToFree;
}

int libMemTabP(char **tab){
    free(*tab);
    // forcer la libération de la mémoire
    *tab = NULL;
    return allMemory;
}

void displayMemoryAllocate(){
    struct memoryBlock *curr = bl;
    int i = 1;
    while(curr != NULL){
        printf("Bloc %d : %ld octets, free : %d\n", i++, curr->size, curr->free);
        if(curr->next == NULL) break;
        curr = curr->next;
    }
}