/**
 * @file test.h
 * @author Zacharie and Paul
 *
 * This file contains the prototype of the functions which will be use in the @see test.c
 * for launch and manage the test programm.
 *
 */

#ifndef __test_h
#define __test_h

#define OPERATION_SIZE 30

/**
 * @brief Launch the command line mode where user write all operations to do 
 when he launches the programm.
 * 
 * @param argc given number of arguments
 * @param argv table of operations (arguments) to do
 */
void commandLine(int argc, char **argv);

/**
 * @brief Launch the interactive mode where user write the operations
 * who wants to do with a indicative menu.
 * 
 */
void interactive();

/**
 * @brief Empty the standard input buffer which can sometime still of data after 
 * the reading.
 * 
 */
void emptyBuffer();

/**
 * @brief Read a message on the standard input and put this on the string parameter.
 * 
 * @param string table of caracters to fill
 * @param size of string
 * @return int 1 on success, 0 on failure
 */
int readE(char *string, int size);

/**
 * @brief Allows to read the operation writen by user or in a file,
 * this can to be an allocation, a deallocation or the finish of the programm.
 * 
 * @param string table which store the operation taping by the user
 */
int executeOperation(char *string);

/**
 * @brief Extract the number of bytes in a string write by the user.
 * 
 * @param string where we extract number
 * @param firstChar position of beginnig of number
 * @return int number of bytes write in the string
 */
int extractNBYtes(char *string, int firstChar);

#endif