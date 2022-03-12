/**
 * @file file_handler.h
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

//Inculsion " " ou < >
#ifndef STDIO_H
#include <stdio.h>
#endif

//Declaration Macro et macro fonctions
#define MATRICE_SIZE 12

//Declaration des types
typedef struct {
    char matrice[MATRICE_SIZE][MATRICE_SIZE];
}Matrice;

//Declaration des fonctions publique avec leurs doctring

/**
 * @brief Open the file in read mode and return it if he exist. Null otherwise.
 * 
 * @param file_name Name or path to the file to open.
 * @return FILE* poiter to the file or null if an error occued. 
 */
FILE *open_file(const char *file_name);

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
Matrice get_matrice(FILE *file);

/**
 * @brief Initialise a macro of the number of words in file. 
 * The pointor position after read and count is replaced at 
 * initial position (first word, first char).
 * 
 * @param file FILE* where words are listed (1 by line)
 */
int get_number_words(FILE *file);

/**
 * @brief Get a list of type char[][] containing all the words
 * in the file.
 * 
 * @param file FILE* where words are listed (1 by line)
 * @return Words 
 */
char** get_words(FILE *file, int nb_words);

/**
 * @brief 
 * 
 * @param matrice 
 */
void print_matrice(Matrice matrice);

/**
 * @brief 
 * 
 * @param words_array 
 * @param number_words 
 */
void print_words(char ** words_array, int number_words);

