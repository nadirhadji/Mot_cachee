/**
 * @file file_handler.h
 * @author Hadji Nadir - HADN08069703
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//************Macro***********
#define GRID_SIZE 12

//************Types************
typedef struct {
    char **grid;
    char **words;
    int words_count;
}Game;

//************Public functions**********

/**
 * @brief Print to stdout the current state of the grid
 * with the value of each char at each cell. 
 * 
 * @param grid Pointer to char array containing the game grid.
 */
void print_grid(char **grid);

/**
 * @brief Print to stdout the list of words
 * 1 by row
 * 
 * @param words_list Pointer to char array containing the list
 * @param nb_words Number of words in the grid
 */
void print_words(char ** words_list, int nb_words);

/**
 * @brief Create an object of type Game from a file.
 * 
 * Game object will contain : 
 *  - the game grid : char**
 *  - the words list : char**
 *  - number of words in words list : int 
 * 
 * The game grid and words list are arrays allocated on the Heap.
 * *IMPORTANT* need to call delete_game after usage to free the
 * allocated memory. 
 * 
 * @param file_name the name of the file containing the game data.
 * @return Game Object of type Game containing the game data.
 */
Game new_game(char* file_name);

/**
 * @brief Delete all the allocated memory related to a Game object
 * 
 * @param game The Game object.
 */
void delete_game(Game game);