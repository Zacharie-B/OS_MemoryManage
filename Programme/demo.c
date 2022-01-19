/**
 * @file demo.c
 * @author Zacharie and Paul
 * @brief File of demonstration to manage a memory zone.
 * @version 1.0
 *
 * Demonstration programm where we manage memory blocks with the best fit strategy.
 *
 */

#include "myfree.h"
#include "allocate.h"

/**
 * @brief display the number of bytes set free if not equals -1, a error message else
 * 
 * @param nBytes number of bytes set free by myfree function
 */
void displayMemoryFree(int nBytes){
    static int turn = 0;
    if(nBytes == -1){
        puts ("The memory can't be set free");
    }
    else{
        printf("Release n° %d, number of bytes set free : %d\n", ++turn, nBytes);
    }
}

/**
 * @brief This is main function which initialize the programm for the demonstration.
 * 
 * @return int result of programm 0 on success, 1 on failure
 */
int main(){
    int sizeSharedMemory = 10000;
    allMemory = initMemory(sizeSharedMemory);
    printf("Number of bytes to allocate for initialization is %ld\n\n", allMemory);
    
    bt = (BlockTable*)malloc(sizeof(BlockTable));
    bt->block = (struct memoryBlock **)malloc(sizeof(struct memoryBlock));
    bt->indexMax = 0;

    for(int turn = 0; turn < 9; turn++){
        puts("");
        /** We allocate a memory block */
        if((turn < 2) || (turn == 3) || (turn == 5)){
            int nBytes = (int) (random() % (allMemory / 2));
            bt->block[bt->indexMax] = mymalloc(nBytes);
            if(bt->block[bt->indexMax] == 0)
                puts("Nous n'avons pas réussi à allouer le bloc demandé");
            else
                bt->indexMax++;
        }
        /** We deallocate a memory block */
        else if((turn == 2) || (turn == 4) || (turn == 6) || (turn == 7)){
            int blockNum = (int) (random() % 4);
            int nBytes = myfree(bt->block[blockNum]);
            if(nBytes == -1)
                printf("Le bloc n° %d n'est pas alloué, il ne peut donc pas être libéré\n", blockNum + 1);
            else{
                printf("Vous avez libérer : %d octets dans la mémoire\n", nBytes);
            }
        }
        /** We finist the programm */
        else if(turn == 8){
            int bytesFree = freeMemory();
            printf("\nVous avez libérer %d octets en mémoire avant de finir le programme\n", bytesFree);
            return 0;
        }
        puts("");
        displayMemoryAllocate();
    }
    return 1;
}