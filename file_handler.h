/**
 * @file file_handler.h
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#ifndef FILE_HANDLER.H
#define FILE_HANDLER.H
#endif

//Inculsion " " ou < >
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

//Declaration Macro et macro fonctions
#define MATRICE_SIZE 12
#define NUMBER_WORDS 10

//Declaration des types
struct Grid {
    char matrice[MATRICE_SIZE][MATRICE_SIZE];
};

struct Words {
    char words_list[NUMBER_WORDS][MATRICE_SIZE];
};

//Declaration des fonctions publique avec leurs doctring

/**
 * @brief Open the file in read mode and return it if he exist. Null otherwise.
 * 
 * @param file_name Name or path to the file to open.
 * @return FILE* poiter to the file or null if an error occued. 
 */
FILE *open_file(char *file_name);

/**
 * @brief Close the file given in parameter
 * 
 * @param file *FILE type object
 * @return int 0 if closed, -1 if not
 */
int close_file(FILE *file);

/**
 * @brief Get the Grid object field with the grid in the file
 * 
 * @param file FILE* where the grid of chars is. 
 * @return Grid struct of type Grid containing char[12][12].
 */
Grid get_matrice(FILE *file);

/**
 * @brief Initialise a macro of the number of words in file. 
 * The pointor position after read and count is replaced at 
 * initial position (first word, first char).
 * 
 * @param file FILE* where words are listed (1 by line)
 */
void define_number_words(FILE *file);

/**
 * @brief Get a list of type char[][] containing all the words
 * in the file.
 * 
 * @param file FILE* where words are listed (1 by line)
 * @return Words 
 */
Words get_words(FILE *file);






