/**
 * @file test.c
 * @author Zacharie and Paul
 * @brief File of test to manage a memory zone.
 * @version 1.0
 * 
 * Test Programm where the user choose how manage a memory zone, he can 
 * use 3 modes : operation by operation, all operations in the command line
 * at launch of the programm or all operations in a configuration file to inform
 * at launch of the programm.
 *
 */

#include "allocate.h"
#include "myfree.h"
#include "test.h"

static char string[OPERATION_SIZE];

/**
 * @brief This is main function which initialize the programm for the test modes.
 * 
 * @param argc number of arguments in the command line
 * @param argv table of arguments in the command line
 * @return int result of programm 0 on success, 2 on failure
 */
int main(int argc, char **argv){
    /** test programm in interactive mode */
    if(!strcmp(argv[1], "-i")){
        interactive();
    }

    /** test programm in batch mode */
    else if(!strcmp(argv[1], "-f")){
        FILE *file = NULL;
        file = fopen(argv[2], "r");
        if(file != NULL){
            bt = (BlockTable *)malloc(sizeof(BlockTable));
            bt->block = (struct memoryBlock **)malloc(sizeof(struct memoryBlock));
            bt->indexMax = 0;
            if(fgets(string, OPERATION_SIZE, file) != NULL){
                if(!strncmp(string, "init", 4)){
                    int nBytes = extractNBYtes(string, 5);
                    allMemory = initMemory(nBytes);
                    printf("Mémoire totale alloué : %ld octets\n", allMemory);
                }
                else{
                    return 2;
                }
            }
            while(fgets(string, OPERATION_SIZE, file) != NULL){
                executeOperation(string);
            }
            fclose(file);
        }
        else{
            puts("Impossible d'ouvrir le fichier demandé");
        }
        return 0;
    }

    /** test programm in command line mode*/
    else{
        commandLine(argc, argv);
    }
    return 0;
}

void commandLine(int argc, char **argv){
    if(!strncmp(argv[1], "init", 4)){
        int nBytes = atoi(argv[2]);
        allMemory = initMemory(nBytes);
    }
    else{
        exit(1);
    }

    printf("Vous avez alloué %ld octets\n", allMemory);
    printf("################################################################\n");

    bt = (BlockTable*)malloc(sizeof(BlockTable));
    bt->block = (struct memoryBlock**)malloc(sizeof(struct memoryBlock));
    bt->indexMax = 0;
    for(int i = 1; i < (argc / 2); i++){
        puts("");
        /** when the user wants allocate memory */
        if(!strcmp("al", argv[(i * 2) + 1])){
            int nBytes = atoi(argv[(i * 2) + 2]);

            bt->block[bt->indexMax] = mymalloc(nBytes);
            
            if(bt->block[bt->indexMax] == 0)
                puts("Nous n'avons pas réussi à allouer le bloc demandé");
            else
                bt->indexMax++;
        }
        /** when the user wants set free memory */
        else if(!strcmp("lib", argv[(i * 2) + 1])){
            int numBlock = atoi(argv[(i * 2) + 2]);
            int nBytes = myfree(bt->block[numBlock - 1]);
            if(nBytes == -1)
                printf("Le bloc n° %d n'est pas alloué, il ne peut donc pas être libéré\n", numBlock);
            else{
                printf("Vous avez libérer : %d octets dans la mémoire\n", nBytes);
            }
        }
        /** when the user wants finish the programm */
        else if(!strcmp("end", argv[(i * 2) + 1])){
            int result = freeMemory();
            printf("Le programme se termine, vous avez libérer %d octets\n", result);
            exit(0);
        }
        printf("Nombre de blocs : %d\n", bt->indexMax + 1);
        displayMemoryAllocate();
    }
}

void interactive(){
    printf("####################################################################\n");
    printf("Veuillez initialiser la mémoire du programme :\nTapez init <taille> (en octets)\n");

    while(1){
        if(readE(string, OPERATION_SIZE)){
            if(!strncmp(string, "init", 4)){
                int nBytes = extractNBYtes(string, 5);
                allMemory = initMemory(nBytes);
                printf("Vous avez alloué %ld octets\n", allMemory);
                printf("################################################################\n");
                break;
            }
            else{
                printf("Mauvaise initialisation, veuillez suivre la syntaxe décrite ci-dessus\n");
            }
        }
        else{
            printf("Erreur de lecture du message\n");
        }
    }
    bt = (BlockTable *)malloc(sizeof(BlockTable));
    bt->block = (struct memoryBlock **)malloc(sizeof(struct memoryBlock));
    bt->indexMax = 0;
    while(1){
        printf("\n################################################################\n");
        puts("Pour allouer de la mémoire : al <taille> (en octets)");
        puts("Pour libérer un bloc de mémoire : lib <numéro du bloc>");
        puts("Pour libérer toute la mémoire et finir le programme : end");
        if(readE(string, OPERATION_SIZE))
            executeOperation(string);
        else
            puts("Il y a eu un problème de lecture de votre message");
    }
}

int executeOperation(char *string){

    /** We get the instruction of user and we analyse to verify if it has the right
     * syntax and we launch the associated operation. */
    puts("");
    /** if the user wants allocate memory */
    if(!strncmp(string, "al", 2)){
        int nBytes = extractNBYtes(string, 3);
        if(nBytes <= 0){
            puts("Il faut saisir un nombre strictement supérieur à 0");
            return 0;
        }
        bt->block[bt->indexMax] = mymalloc(nBytes);
        if(bt->block[bt->indexMax] == 0)
            puts("Nous n'avons pas réussi à allouer le bloc demandé");
        else{
            bt->indexMax++;
        }
    }
    /** if the user wants set free a memory block */
    else if(!strncmp(string, "lib", 3)){
        int blockNum = extractNBYtes(string, 4);
        blockNum--;
        if(blockNum <= bt->indexMax){
            int nBytes = myfree(bt->block[blockNum]);
            if(nBytes == -1)
                printf("Le bloc n° %d n'est pas alloué, il ne peut donc pas être libéré\n", blockNum + 1);
            else{
                printf("Vous avez libérer : %d octets dans la mémoire\n", nBytes);
            }
        }
        else
            printf("Le bloc n° %d ne fait pas parti de la zone de mémoire\n", blockNum + 1);
    }
    /** if the user wants to end the programm */
    else if(!strncmp(string, "end", 3)){
        int memoryFree = freeMemory();
        printf("Le programme se termine, vous avez libérer %d octets\n", memoryFree);
        exit(0);
    }
    else
        puts("Veuillez respecter la syntaxe décrite ci-dessus");
    
    puts("");
    printf("Nombre de blocs : %d\n", bt->indexMax + 1);
    displayMemoryAllocate();
}

int extractNBYtes(char *string, int firstNumber){
    char *pointer = string;
    pointer += firstNumber;
    int number = atoi(pointer);
    return number;
}

void emptyBuffer(){
    int c = 0;
    while (c != '\n' && c != EOF){
        c = getchar();
    }
}
 
int readE(char *chaine, int longueur){
    char *positionEntree = NULL;
    if (fgets(chaine, longueur, stdin) != NULL){
        positionEntree = strchr(chaine, '\n');
        if (positionEntree != NULL){
            *positionEntree = '\0';
        }
        else{
            emptyBuffer();
        }
        return 1;
    }
    else{
        emptyBuffer();
        return 0;
    }
}