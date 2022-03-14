/**
 * @file solver.h
 * @author Hadji Nadir - HADN08069703
 * @brief 
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 */

#include <stdbool.h>
#include <ctype.h>
#include "file_handler.h"

#define GRID_SIZE 12

typedef enum {
   RIGHT,
   LEFT,
   ABOVE,
   UNDER,
   NO
}Orientation;

typedef struct {
    int row;
    int column;
}Point;

typedef struct {
    Orientation orientation;
    int size;
    Point point;
}Position;

typedef struct {
    Position **list;
    int count;
}Solution;

/**
 * @brief Process the file if found and search the hidden words in it.
 * 
 * The found word will be stored in the parameter hidden_word.
 * This function orchester the internal behavior of the module.
 * 
 * @param file_name Name of the file containing the game data
 * @param hidden_word Empty string to be field 
 */
void get_hidden_word(char *file_name, char *hidden_word);
